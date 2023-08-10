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
  if (getAlt() < 213) { // 0-700 ft: 10deg
    writeS1(80);
    writeS2(80);
  } else if (getAlt() > 213 && getAlt() < 246) { // 700-810ft: 20deg
    writeS1(70);
    writeS2(70);
  } else if (getAlt() > 246) { // 810ft+: 45deg airbrakes
    writeS1(45);
    writeS2(45);
  }
}

const float LANDED_THRESHOLD = 0.05; // Velocity on the ground
const float LANDED_ALT_THRESHOLD = 1.25; // Have to be within this far from starting alt to be landed
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