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
#include <SdFat.h>
#include <SPI.h>

Adafruit_FlashTransport_SPI flashTransport(SS, SPI);
Adafruit_SPIFlash flash(&flashTransport);
FatVolume fatfs;
File32 dataFile;

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

void setupData() {
  Serial.println("Initializing FS...");
  if (!flash.begin()) {
    Serial.println("Failed to initialize Flash");
  }
  if (!fatfs.begin(&flash)) {
    Serial.println("Failed to initialize FS");
  }
}

unsigned long startTime = 0;
void startRecording() {
  // Find datafile
  int i = 0;
  while (true) {
    String name = String(i) + ".txt";
    if (!fatfs.exists(name)) {
      dataFile = fatfs.open(name, FILE_WRITE);
    }
  }
  
  startTime = millis();
}

void stopRecording() {
  dataFile.close();
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
  
  dataFile.write(&data, sizeof(DataFrame));
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