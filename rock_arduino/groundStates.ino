unsigned long lastWrite = millis();
const int writeInterval = 250;

extern enum STATE;

bool canWrite() {
  unsigned long currentTime = millis();
  bool ok = (currentTime - lastWrite) > writeInterval;
  lastWrite = currentTime;
  return ok;
}

void groundState() {
  bleReadState(); // Wait for READY command
  bleServoPositionsRead();
  if (canWrite()) {
    bleWriteState();
    bleWriteSensors();
  }
}

const int LAUNCH_THRESHOLD = 1;

void readyState() {
  if (BLE.connected()) {
    BLE.disconnect();
  }
  if (!recording()) {
    startRecording();
  }

  writeData();

  if (getAccel() > LAUNCH_THRESHOLD) {
    setState(STATE_RISING);
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