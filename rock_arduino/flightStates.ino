#include "states.h"

const float DESCENT_THRESHOLD = -1; // Descent velocity (m/s)
const float DESCENT_ALT_THRESHOLD = 3; // Have to be > this height (m) to begin descent

void ascentState() {
  #ifdef DEBUG
  Serial.println("ASCENT");
  #endif

  ledWrite(0, 255, 0);
  writeData();

  if (getVel() < DESCENT_THRESHOLD && getAlt() > DESCENT_ALT_THRESHOLD) {
    setState(STATE_DESCENT);
  }

  // FLIGHT CONTROL
  /*if (getAlt() < 213) { // 0-700 ft: 10deg
    writeS3(89);
    writeS2(89);
  } else if (getAlt() > 213 && getAlt() < 230) { // 700-750ft: 20deg
    writeS3(85);
    writeS2(85);
  } else if (getAlt() > 230) { // 750ft+: 45deg airbrakes
    writeS3(45);
    writeS2(45);
  }*/
  writeS3(90);
  writeS2(90);
}

const float LANDED_THRESHOLD = 0.05; // Velocity on the ground
const float LANDED_ALT_THRESHOLD = 1.25; // Have to be within this far from starting alt to be landed
void descentState() {
  #ifdef DEBUG
  Serial.println("DESCENT");
  #endif

  ledWrite(0, 0, 255);
  writeData();

  writeS3(90);
  writeS2(90);

  if (abs(getVel()) < LANDED_THRESHOLD && abs(getAlt()) < LANDED_ALT_THRESHOLD) {
    stopRecording();
    setState(STATE_TRANSFER);
    writeS1(90);
    writeS2(90);
    writeS3(90);
    transfer();
  }
}