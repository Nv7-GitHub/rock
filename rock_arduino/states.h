#pragma once

enum STATE {
  STATE_NONE = 0,    // No state
  STATE_GROUND = 1,  // You turn on the rocket, see data on app
  STATE_READY = 2,   // App arms rocket & disconnects
  STATE_ASCENT = 3,  // Start flying up
  STATE_APOGEE = 4,  // Apogee detected
  STATE_DESCENT = 5, // Going down
  STATE_LANDED = 6,  // On the ground, BLE broadcasting file
};