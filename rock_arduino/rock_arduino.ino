void setup() {
  Serial.begin(9600);
  // TODO: Delete this when running flight comp by itself
  while (!Serial) {
    delay(1);
  }
  setupSensors();
  setupBle();
  setupData();
}

void loop() {
  if (!readSensors()) {
    Serial.println("SENSOR READ FAILED");
    return;
  }
  stateMachine();
}