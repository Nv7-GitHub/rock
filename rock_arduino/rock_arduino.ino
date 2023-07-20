void setup() {
  Serial.begin(9600);
  setupSensors();
}

void loop() {
  if (!readSensors()) {
    Serial.println("SENSOR READ FAILED");
    return;
  }
  stateMachine();
}