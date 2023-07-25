#include "states.h"
#include <SPI.h>
#include <Adafruit_SPIFlash.h>

Adafruit_FlashTransport_SPI flashTransport(SS, SPI);
Adafruit_SPIFlash flash(&flashTransport);

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

// https://github.com/adafruit/Adafruit_SPIFlash/blob/1cd95724810c3dc845d7dbb48092f87616c8a628/examples/SdFat_full_usage/SdFat_full_usage.ino

uint32_t frameCount = 0;
uint8_t frameBuffer[sizeof(DataFrame)];
void setupData() {
  if (!flash.begin()) {
    Serial.println("Failed to initialize Flash");
  }

  // Check for data
  int frameCount = checkFrameCount();
  Serial.print(frameCount);
  Serial.println(" frames available");
}

unsigned long startTime = 0;
void startRecording() {
  frameCount = 0;
  Serial.println("Erasing flash...");
  /*if (!flash.eraseChip()) {
    Serial.println("Failed to erase flash");
  }
  flash.waitUntilReady();
  */
  int cnt = checkFrameCount();
  memset(frameBuffer, 255, sizeof(frameBuffer));
  for (uint32_t i = 0; i < cnt; i++) {
    flash.writeBuffer(i * sizeof(frameBuffer), frameBuffer, sizeof(frameBuffer));
  }
  Serial.println("Erased flash");
  startTime = millis();
}

void stopRecording() {
  startTime = 0;
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

void writeData() {
  DataFrame data;
  data.time = millis() - startTime;
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
  memcpy(frameBuffer, &data, sizeof(data));
  flash.writeBuffer(frameCount * sizeof(frameBuffer), frameBuffer, sizeof(frameBuffer));
  frameCount++;
}

bool checkFrame(int addr) {
  memset(frameBuffer, 255, sizeof(frameBuffer));
  flash.readBuffer(addr * sizeof(frameBuffer), frameBuffer, sizeof(frameBuffer));
  for (int i = 0; i < sizeof(frameBuffer); i++) {
    if (frameBuffer[i] != 255) {  // Frame buffer has data
      // Use this code to read the data from the frame
      /*// Read frame
      DataFrame data;
      memcpy(&data, &frameBuffer, sizeof(frameBuffer));
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

void transmitData() {
  // TODO: Transmit data, probably something like https://github.com/petewarden/ble_file_transfer (see below)
  /* 
  When the client has a file to send, it first writes the file length and CRC32 checksum to characteristics on the device.
  Then it starts a file transfer by writing an integer of 1 to the command characteristic.
  The device then expects the client to repeatedly write sequential blocks of 128 bytes or less to the file block characteristic, waiting until one has been acknowledged before sending the next.
  The client assembles these blocks into a contiguous array of data.
  Once the expected number of bytes has been received, the device confirms the checksum matches the one supplied by the client, and then calls the onBLEFileReceived function with the received data.
  The client is notified that the file transfer succeeded through a notification of the transfer code as 0.
  */
  setState(STATE_GROUND);
}