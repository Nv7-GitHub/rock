const int APOGEE_THRESHOLD = 0.5; // Apogee of vertical velocity is less than this value (m/s)

extern enum STATE;

void ascentState() {
  writeData();

  if (getVel() < APOGEE_THRESHOLD) {
    setState(STATE_APOGEE);
  }
}

const int DESCENT_THRESHOLD = -0.5; // Apogee of descent velocity

void apogeeState() {
  writeData();

  if (getVel() < DESCENT_THRESHOLD) {
    setState(STATE_DESCENT);
  }
}

const int LANDED_THRESHOLD = 0.1; // Velocity on the ground
void descentState() {
  writeData();

  if (abs(getVel()) < LANDED_THRESHOLD) {
    landedTransition();
  }
}