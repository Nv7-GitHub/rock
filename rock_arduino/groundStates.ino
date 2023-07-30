#include "states.h"

unsigned long lastWrite = millis();
const int writeInterval = 250;

bool canWrite() {
  unsigned long currentTime = millis();
  bool ok = (currentTime - lastWrite) > writeInterval;
  if (ok) {
    lastWrite = currentTime;
  }
  return ok;
}

void groundState() {
  if (!BLE.connected()) {
    #ifdef DEBUG
    Serial.println("BLE disconnected");
    #endif
    return;
  }

  bleReadState(); // Wait for READY command
  bleServoPositionsRead();
  if (canWrite()) {
    #ifdef DEBUG
    Serial.println("BLUETOOTH WRITE");
    #endif
    bleWriteState();
    bleWriteSensors();
  }
}

const int LAUNCH_THRESHOLD = 1;

void readyState() {
  Serial.println("READY STATE");
  if (BLE.connected()) {
    BLE.disconnect();
  }
  if (!recording()) {
    startRecording();
  }

  writeData();

  if (getAccel() > LAUNCH_THRESHOLD) {
    setState(STATE_ASCENT);
  }

  // DEBUG
  if (flightTime() > 250) {
    landedTransition();
  }
}

void landedTransition() {
  setState(STATE_LANDED);
  stopRecording();
  BLE.advertise();
}

void landedState() {
  transmitData();
}