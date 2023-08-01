#include "states.h"

const int APOGEE_THRESHOLD = 0.2; // Apogee of vertical velocity is less than this value (m/s)

void ascentState() {
  #ifdef DEBUG
  Serial.println("ASCENT");
  #endif
  ledWrite(0, 255, 0);
  writeData();

  if (getVel() < APOGEE_THRESHOLD) {
    setState(STATE_APOGEE);
  }
}

const int DESCENT_THRESHOLD = -0.2; // Apogee of descent velocity

void apogeeState() {
  #ifdef DEBUG
  Serial.println("APOGEE");
  #endif
  ledWrite(0, 255, 255);
  writeData();

  if (getVel() < DESCENT_THRESHOLD) {
    setState(STATE_DESCENT);
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
    landedTransition();
  }
}