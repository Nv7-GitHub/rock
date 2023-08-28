#include "states.h"
#include <SPI.h>
#include <Adafruit_SPIFlash.h>

Adafruit_FlashTransport_SPI flashTransport(SS, SPI);
Adafruit_SPIFlash flash(&flashTransport);

#pragma pack(push,1)
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
#pragma pack(pop)

const int FRAME_SIZE = sizeof(DataFrame);

// https://github.com/adafruit/Adafruit_SPIFlash/blob/1cd95724810c3dc845d7dbb48092f87616c8a628/examples/SdFat_full_usage/SdFat_full_usage.ino

uint32_t frameCount = 0;
const int FRAME_BUFF_SIZE = 10;
uint8_t frameBuffer[sizeof(DataFrame) * FRAME_BUFF_SIZE];
int buff_space = 0;
void setupData() {
  if (!flash.begin()) {
    setupError("Failed to initialize flash");
  }

  // Transfer data if frames available
  if (hasData()) {
    setState(STATE_TRANSFER);
    transfer();
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

bool hasData() {
  uint8_t buff[1] = {255};
  flash.readBuffer(0, buff, sizeof(buff));
  for (int i = 0; i < sizeof(buff); i++) {
    if (i != 255) {
      return true;
    }
  }
  return false;
}

void serialWait() {
  while (!Serial.available() > 0) { // Wait for sender to send "1"
    delay(1);
  }
  Serial.read();
}

void transfer() {
  // Get sector count
  int sectorCount = 0;
  while (true) {
    uint8_t buf[4096];
    memset(buf, 255, sizeof(buf));
    flash.readBuffer(sectorCount * 4096, buf, 4096);
    bool hasData = false;
    for (int i = 0; i < sizeof(buf); i++) {
      if (buf[i] != 255) {
        hasData = true;
        break;
      }
    }
    if (!hasData) {
      break;
    }
    sectorCount++;
    if (sectorCount > 8000000/4096) {
      break;
    }
  }

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

  // Write sector count
  Serial.write((char*)(&sectorCount), sizeof(sectorCount));
  serialWait();

  // Transfer frames
  for (int i = 0; i < sectorCount; i++) {
    uint8_t buf[4096];
    memset(buf, 255, sizeof(buf));
    flash.readBuffer(sectorCount * 4096, buf, 4096);
    Serial.write(buf, sizeof(buf));
    serialWait();
  }

  // Wait for OK
  serialWait();

  // Erase
  for (int i = 0; i < sectorCount; i++) {
    flash.eraseSector(i);
  }
  Serial.write(1);

  // Move on
  setState(STATE_GROUND);
}