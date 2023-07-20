// State machine for the rocket

enum STATE {
  STATE_GROUND = 0, // You turn on the rocket, see data on app
  STATE_READY = 1, // App arms rocket & disconnects
  STATE_ASCENT = 2, // Start flying up
  STATE_APOGEE = 3, // Apogee detected
  STATE_DESCENT = 4, // Going down
  STATE_LANDED = 5, // On the ground, BLE broadcasting file
};

int state = STATE_GROUND;
int getState() {
  return state;
}
void setState(int newState) {
  state = newState;
}

void stateMachine() {
  switch (state) {
    case STATE_GROUND:
      groundState();
      break;
    
    case STATE_READY:
      readyState();
      break;

    case STATE_ASCENT:
      ascentState();
      break;

    case STATE_APOGEE:
      apogeeState();
      break;

    case STATE_DESCENT:
      descentState();
      break;
    
    case STATE_LANDED:
      landedState();
      break;
  }
}