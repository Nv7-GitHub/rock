/* 
Data Recorded:
- Time (millis)
- State
- Accel value
- Velocity value
- Altitude value
- Servo angle
- Raw sensor vals (accelX, accelY, accelZ, barometer)
*/

#include "states.h"

unsigned long startTime = 0;
void startRecording() {
  startTime = millis();
}
void stopRecording() {
  startTime = 0;
}

bool recording() {
  return startTime != 0;
}

void writeData() {
  // TODO: Implement
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