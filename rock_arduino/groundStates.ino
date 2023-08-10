#include "states.h"

const int LAUNCH_THRESHOLD = 35; // m/s^2

void groundState() {
  #ifdef DEBUG
  Serial.println("READY");
  #endif

  ledWrite(255, 0, 0);

  if (getAccel() > LAUNCH_THRESHOLD) {
    setState(STATE_ASCENT);
  }
}

