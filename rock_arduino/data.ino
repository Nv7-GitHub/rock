#include "states.h"
#include <SPI.h>
#include <Adafruit_SPIFlash.h>

Adafruit_FlashTransport_SPI flashTransport(SS, SPI);
Adafruit_SPIFlash flash(&flashTransport);

#pragma pack
struct DataFrame {
  unsigned long time;
  int state;
  float accel;
  float vel;
  float alt;
  float roll;
  int s1;
  int s2;
  int s3;
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float baro;
  float temp;
};
const int FRAME_SIZE = sizeof(DataFrame);

// https://github.com/adafruit/Adafruit_SPIFlash/blob/1cd95724810c3dc845d7dbb48092f87616c8a628/examples/SdFat_full_usage/SdFat_full_usage.ino

uint32_t frameCount = 0;
const int FRAME_BUFF_SIZE = 10;
uint8_t frameBuffer[sizeof(DataFrame) * FRAME_BUFF_SIZE];
uint8_t singleFrameBuffer[sizeof(DataFrame)];
int buff_space = 0;
void setupData() {
  if (!flash.begin()) {
    Serial.println("Failed to initialize Flash");
    ledWrite(0, 255, 0);
    delay(1000);
  }

  // Check for data
  int frameCount = checkFrameCount();
  Serial.print(frameCount);
  Serial.println(" frames available");

  // Transfer data if frames available
  if (frameCount > 0) {
    setState(STATE_TRANSFER);
    transfer();
  }
}

void eraseFlash() {
  #ifdef DEBUG
  Serial.println("Erasing flash...");
  #endif

  // Erase sectors needed
  int eraseCnt = (checkFrameCount() * sizeof(singleFrameBuffer)) / 4096 + 1;
  for (int i = 0; i < eraseCnt; i++) {
    flash.eraseSector(i);
  }
}

unsigned long startTime = 0;
void startRecording() {
  frameCount = 0;
  startTime = millis();
  sensorStartRecording();
}

void stopRecording() {
  startTime = 0;

  // Write remaining frames
  flash.writeBuffer(frameCount * sizeof(frameBuffer), frameBuffer, sizeof(frameBuffer));
  frameCount++;
  buff_space = 0;
  memset(frameBuffer, 255, sizeof(frameBuffer));
}

bool recording() {
  return startTime != 0;
}

extern float accelx;
extern float accely;
extern float accelz;

extern float gyrox;
extern float gyroy;
extern float gyroz;

extern float baroAlt;

unsigned long flightTime() {
  return millis() - startTime;
}

void writeData() {
  DataFrame data;
  data.time = flightTime();
  data.state = getState();
  data.accel = getAccel();
  data.vel = getVel();
  data.alt = getAlt();
  data.roll = getRoll();
  data.s1 = readS1();
  data.s2 = readS2();
  data.s3 = readS3();
  data.ax = accelx;
  data.ay = accely;
  data.az = accelz;
  data.gx = gyrox;
  data.gy = gyroy;
  data.gz = gyroz;
  data.baro = baroAlt;
  data.temp = getTemp();


  // Write data
  memcpy(&frameBuffer[buff_space * sizeof(data)], &data, sizeof(data));
  buff_space++;
  if (buff_space == FRAME_BUFF_SIZE) {
    flash.writeBuffer(frameCount * sizeof(frameBuffer), frameBuffer, sizeof(frameBuffer));
    frameCount++;
    buff_space = 0;
    memset(frameBuffer, 255, sizeof(frameBuffer));
  }
}

bool checkFrame(int addr) {
  memset(singleFrameBuffer, 255, sizeof(singleFrameBuffer));
  flash.readBuffer(addr * sizeof(singleFrameBuffer), singleFrameBuffer, sizeof(singleFrameBuffer));
  for (int i = 0; i < sizeof(singleFrameBuffer); i++) {
    if (singleFrameBuffer[i] != 255) {  // Frame buffer has data
      // Use this code to read the data from the frame
      /*// Read frame
      DataFrame data;
      memcpy(&data, &singleFrameBuffer, sizeof(singleFrameBuffer));
      Serial.print("Frame time: ");
      Serial.println(data.time);*/
      return true;
    }
  }
  return false;
}

int checkFrameCount() {
  int addr = 0;
  while (checkFrame(addr)) {
    addr++;
  }
  return addr;
}

void serialWait() {
  while (!Serial.available() > 0) { // Wait for sender to send "1"
    delay(1);
  }
  Serial.read();
}

void transfer() {
  // INIT
  ledWrite(0, 255, 255);
  while (!Serial) {
    delay(1);
  }
  delay(100); // Wait for transfer to start up
  
  // Begin transfer
  Serial.println("TRANSFER BEGIN");
  Serial.write(1);
  serialWait();

  // Write frame count
  int frameCount = checkFrameCount();
  Serial.write((char*)(&frameCount), sizeof(frameCount));
  serialWait();

  // Transfer frames
  for (int i = 0; i < frameCount; i++) {
    memset(singleFrameBuffer, 255, sizeof(singleFrameBuffer));
    flash.readBuffer(i * sizeof(singleFrameBuffer), singleFrameBuffer, sizeof(singleFrameBuffer));
    Serial.write(singleFrameBuffer, sizeof(singleFrameBuffer));
    serialWait();
  }

  // Wait for OK
  serialWait();

  // Erase
  eraseFlash();
  Serial.write(1);

  // Move on
  setState(STATE_GROUND);
}