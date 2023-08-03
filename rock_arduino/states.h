#pragma once

enum STATE {
  STATE_NONE = 0,    // No state, white
  STATE_GROUND = 1,  // Rocket on ground, ready for launch, red
  STATE_ASCENT = 2,  // Start flying up, green
  STATE_DESCENT = 3, // Going down, blue
  STATE_TRANSFER = 4, // Transferring data, state machine not running, cyan
};