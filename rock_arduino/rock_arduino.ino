void setup() {
  Serial.begin(9600);
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