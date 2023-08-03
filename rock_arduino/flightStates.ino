#include "states.h"

const int DESCENT_THRESHOLD = -0.2; // Descent velocity (m/s)

void ascentState() {
  #ifdef DEBUG
  Serial.println("ASCENT");
  #endif
  ledWrite(0, 255, 0);
  writeData();

  if (getVel() < DESCENT_THRESHOLD) {
    setState(STATE_DESCENT);
  }

  // FLIGHT CONTROL
  if (getAlt() < 750) {
    writeS1(1);
    writeS2(1);
  } else if (getAlt() > 750) {
    writeS1(2);
    writeS2(2);
  }
}

const float LANDED_THRESHOLD = 0.05; // Velocity on the ground
void descentState() {
  #ifdef DEBUG
  Serial.println("DESCENT");
  #endif

  ledWrite(0, 0, 255);
  writeData();

  if (abs(getVel()) < LANDED_THRESHOLD) {
    setState(STATE_TRANSFER);
    transfer();
  }
}