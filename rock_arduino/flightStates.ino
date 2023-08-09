#include "states.h"

const float DESCENT_THRESHOLD = -1; // Descent velocity (m/s)
const float DESCENT_ALT_THRESHOLD = 3; // Have to be > this height (m) to begin descent

void ascentState() {
  #ifdef DEBUG
  Serial.println("ASCENT");
  #endif

  if (!recording()) {
    startRecording();
  }

  ledWrite(0, 255, 0);
  writeData();

  if (getVel() < DESCENT_THRESHOLD && getAlt() > DESCENT_ALT_THRESHOLD) {
    setState(STATE_DESCENT);
  }

  // FLIGHT CONTROL
  if (getAlt() < 700) { // 0-700 ft: 3deg
    writeS1(87);
    writeS2(87);
  } else if (getAlt() > 700 && getAlt() < 810) { // 700-810ft: 5deg
    writeS1(84);
    writeS2(84);
  } else if (getAlt() > 810) { // 810ft+: 45deg airbrakes
    writeS1(45);
    writeS2(45);
  }
}

const float LANDED_THRESHOLD = 0.05; // Velocity on the ground
const float LANDED_ALT_THRESHOLD = 0.5; // Have to be this far from starting alt to be landed
void descentState() {
  #ifdef DEBUG
  Serial.println("DESCENT");
  #endif

  ledWrite(0, 0, 255);
  writeData();

  if (abs(getVel()) < LANDED_THRESHOLD && abs(getAlt()) < LANDED_ALT_THRESHOLD) {
    stopRecording();
    setState(STATE_TRANSFER);
    writeS1(90);
    writeS2(90);
    transfer();
  }
}