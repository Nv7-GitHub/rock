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
  int pow = 0;
  while (!Serial) {
    delay(10);
    ledWrite(pow, 0, pow);
    pow++;
    if (pow > 128) {
      pow = 0;
    }
  }
  Serial.println(error);
}

void loop() {
  readSensors();
  predictPos();
  stateMachine();
}