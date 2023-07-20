// State machine for the rocket

enum {
  STATE_GROUND = 0,
  STATE_FLYING = 1,
  STATE_LANDED = 2,
}

int state = STATE_GROUND;

void stateMachine() {
  switch (state) {
    case STATE_GROUND:
      break;
    
    case STATE_FLYING:
      break;

    case STATE_LANDED:
      break;
  }
}