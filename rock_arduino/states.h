#pragma once

enum STATE {
  STATE_GROUND = 0,  // You turn on the rocket, see data on app
  STATE_READY = 1,   // App arms rocket & disconnects
  STATE_ASCENT = 2,  // Start flying up
  STATE_APOGEE = 3,  // Apogee detected
  STATE_DESCENT = 4, // Going down
  STATE_LANDED = 5,  // On the ground, BLE broadcasting file
};