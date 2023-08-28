#include "states.h"

const int LAUNCH_THRESHOLD = 30; // m/s^2

void groundState() {
  #ifdef DEBUG
  Serial.println("READY");
  #endif

  ledWrite(255, 0, 0);

  // Flight initial fin angles
  writeS3(80);
  writeS2(80);

  if (getAccel() > LAUNCH_THRESHOLD) {
    setState(STATE_ASCENT);
  }
}

