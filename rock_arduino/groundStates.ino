#include "states.h"

const int LAUNCH_THRESHOLD = 1; // TODO: make this higher in actual launch

void groundState() {
  #ifdef DEBUG
  Serial.println("READY");
  #endif

  ledWrite(255, 0, 0);
  if (!recording()) {
    startRecording();
  }

  writeData();

  if (getAccel() > LAUNCH_THRESHOLD) {
    setState(STATE_ASCENT);
  }
}

