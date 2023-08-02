#define DEBUG 1

void setup() {
  setupLed();
  ledWrite(255, 255, 255);

  Serial.begin(9600);

  #ifdef DEBUG
  while (!Serial) {
    delay(1);
  }
  Serial.println("CONNECTED");
  #endif

  setupSensors();
  setupBle();
  setupData();
  setupServos();
}

void loop() {
  if (!readSensors()) {
    ledWrite(0, 0, 0);
    return;
  }
  predictPos();
  stateMachine();
}