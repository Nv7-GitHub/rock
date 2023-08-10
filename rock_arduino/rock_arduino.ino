//#define DEBUG 1

#include "states.h"

void setup() {
  setupLed();
  ledWrite(255, 255, 255);

  Serial.begin(9600);

  #if DEBUG
  while (!Serial) {
    delay(10);
  }
  Serial.println("CONNECTED");
  #endif

  setupSensors();
  setupData();
  setupServos();

  setState(STATE_GROUND);
}

void setupError(const char* error) {
  ledWrite(0, 255, 0);
  while (!Serial) {
    delay(10);
  }
  Serial.println(error);
}

void loop() {
  if (!readSensors()) {
    ledWrite(0, 0, 0);
    return;
  }
  predictPos();
  stateMachine();
}