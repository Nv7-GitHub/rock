#include "states.h"

const int APOGEE_THRESHOLD = 0.5; // Apogee of vertical velocity is less than this value (m/s)

void ascentState() {
  ledWrite(false, true, false, false);
  writeData();

  if (getVel() < APOGEE_THRESHOLD) {
    setState(STATE_APOGEE);
  }
}

const int DESCENT_THRESHOLD = -0.5; // Apogee of descent velocity

void apogeeState() {
  ledWrite(false, true, false, false);
  writeData();

  if (getVel() < DESCENT_THRESHOLD) {
    setState(STATE_DESCENT);
  }
}

const int LANDED_THRESHOLD = 0.1; // Velocity on the ground
void descentState() {
  ledWrite(false, true, false, false);
  writeData();

  if (abs(getVel()) < LANDED_THRESHOLD) {
    landedTransition();
  }
}