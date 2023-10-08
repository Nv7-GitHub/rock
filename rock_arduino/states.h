#pragma once

enum STATE {
  STATE_NONE = 0,    // No state, white
  STATE_GROUND = 1,  // Rocket on ground, ready for launch, red, fins sideways
  STATE_READY = 2, // Rocket on pad & recording data, red, fins vertical
  STATE_ASCENT = 3,  // Start flying up, green
  STATE_DESCENT = 4, // Going down, blue
  STATE_TRANSFER = 5, // Transferring data, state machine not running, cyan
};