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
    ledWrite(255, 0, 0);
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

  ledWrite(255, 50, 0);
}

const int LAUNCH_THRESHOLD = 1;

void readyState() {
  #ifdef DEBUG
  Serial.println("READY");
  #endif

  ledWrite(255, 255, 0);
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
}

void landedTransition() {
  setState(STATE_LANDED);
  stopRecording();
  BLE.advertise();
}

void landedState() {
  #ifdef DEBUG
  Serial.println("LANDED");
  #endif

  if (!BLE.connected()) {
    ledWrite(150, 0, 255);
    writeData();
    return;
  }
  ledWrite(255, 0, 190);
  transmitData();
}