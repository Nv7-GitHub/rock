#include "states.h"

int state = STATE_NONE;
int getState() {
  return state;
}
void setState(int newState) {
  state = newState;
}

void stateMachine() {
  switch (state) {
    case STATE_NONE:
      ledWrite(255, 255, 255);
      break;
      
    case STATE_GROUND:
      groundState();
      break;

    case STATE_ASCENT:
      ascentState();
      break;

    case STATE_DESCENT:
      descentState();
      break;
  }
}