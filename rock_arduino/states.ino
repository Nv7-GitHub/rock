#include "states.h"

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