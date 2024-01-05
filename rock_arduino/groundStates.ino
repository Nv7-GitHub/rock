#include "states.h"

void groundState() {
  #ifdef DEBUG
  Serial.println("GROUND");
  #endif

  ledWrite(255, 0, 0);

  // Ground angles
  writeS3(90-maxFinAngle());
  writeS2(90-maxFinAngle());

  if (getGrav() < -9) { // Flipped upside down
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

