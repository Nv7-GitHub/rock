#include "states.h"

const int READY_THRESHOLD = 50; // m/s^2
void groundState() {
  #ifdef DEBUG
  Serial.println("GROUND");
  #endif

  ledWrite(255, 0, 0);

  // Ground angles
  writeS3(30);
  writeS2(30);

  if (getTotalAccel()  > READY_THRESHOLD) {
    setState(STATE_READY);
  }
}

const int LAUNCH_THRESHOLD = 28; // m/s^2
void readyState() {
  #ifdef DEBUG
  Serial.println("READY");
  #endif

  if (!recording()) {
    startRecording();
  }

  ledWrite(255, 0, 0);
  writeData();

  // Flight initial fin angles
  writeS3(90);
  writeS2(90);

  if (getAccel()  > LAUNCH_THRESHOLD) {
    resetControl();
    setState(STATE_ASCENT);
  }
}

