void setup() {
  Serial.begin(9600);
  setupSensors();
}

void loop() {
  if (!readSensors()) {
    
  }
}