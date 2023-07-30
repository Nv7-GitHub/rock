#define DEBUG 1

void setup() {
  setupLed();
  ledWrite(true, false, false, true);

  Serial.begin(9600);

  #ifdef DEBUG
  while (!Serial) {
    delay(1);
  }
  #endif

  setupSensors();
  setupBle();
  setupData();
  setupServos();

  ledWrite(true, false, true, true);
}

void loop() {
  if (!readSensors()) {
    ledWrite(true, false, false, false); // Red
    return;
  }
  predictPos();
  stateMachine();
}