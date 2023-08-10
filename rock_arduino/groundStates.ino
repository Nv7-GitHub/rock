#include "states.h"

const int LAUNCH_THRESHOLD = 2.5; // TODO: make this higher in actual launch

void groundState() {
  #ifdef DEBUG
  Serial.println("READY");
  #endif

  ledWrite(255, 0, 0);

  if (getAccel() > LAUNCH_THRESHOLD) {
    setState(STATE_ASCENT);
  }
}

