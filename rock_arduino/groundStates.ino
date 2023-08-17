#include "states.h"

const int LAUNCH_THRESHOLD = 35; // m/s^2

void groundState() {
  #ifdef DEBUG
  Serial.println("READY");
  #endif

  if (!recording()) {
    startRecording();
  }

  ledWrite(255, 0, 0);
  writeData();

  // Flight initial fin angles
  writeS3(80);
  writeS2(80);

  if (getAccel() > LAUNCH_THRESHOLD) {
    setState(STATE_ASCENT);
  }
}

