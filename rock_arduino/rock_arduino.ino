#define DEBUG 1

void setup() {
  Serial.begin(9600);

  #ifdef DEBUG
  while (!Serial) {
    delay(1);
  }
  #endif

  setupSensors();
  setupBle();
  setupData();
}

void loop() {
  if (!readSensors()) {
    return;
  }
  stateMachine();
}