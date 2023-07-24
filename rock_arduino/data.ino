/* 
Data Recorded:
- Time (millis)
- State
- Accel value
- Velocity value
- Altitude value
- Servo angle
- Roll rate
- Raw sensor vals (accelX, accelY, accelZ, barometer)
*/

#include "states.h"
#include <Adafruit_SPIFlash.h>
#include <SPI.h>

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
};

// https://github.com/adafruit/Adafruit_SPIFlash/blob/1cd95724810c3dc845d7dbb48092f87616c8a628/examples/SdFat_full_usage/SdFat_full_usage.ino

uint32_t frameCount = 0;
uint8_t frameCountBuffer[sizeof(frameCount)];
uint8_t frameBuffer[sizeof(DataFrame)];
void setupData() {
  if (!flash.begin()) {
    Serial.println("Failed to initialize Flash");
  }

  // Check for data
  flash.readBuffer(0, frameCountBuffer, sizeof(frameCountBuffer));
  frameCount = frameBuffer[0] + (frameBuffer[1] << 8) + (frameBuffer[2] << 16) + (frameBuffer[3] << 24);
  Serial.print(frameCount);
  Serial.println(" frames available on flash chip");
}

unsigned long startTime = 0;
void startRecording() {
  frameCount = 0;
  Serial.println("Erasing flash...");
  if (!flash.eraseChip()) {
    Serial.println("Failed to erase flash chip");
  }
  flash.waitUntilReady();
  Serial.println("Erased flash chip");
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


  // Write data
  memcpy(frameBuffer, &data, sizeof(data));
  flash.writeBuffer((frameCount * sizeof(frameBuffer)) + sizeof(frameCountBuffer), frameBuffer, sizeof(frameBuffer));
  frameCount++;
  memcpy(frameCountBuffer, &frameCount, sizeof(frameCount));
  flash.writeBuffer(0, frameCountBuffer, sizeof(frameCountBuffer));
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