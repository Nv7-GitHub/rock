void setupLed() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDG, OUTPUT);
}

void ledWrite(int red, int green, int blue) {
  analogWrite(LEDR, 255-red);
  analogWrite(LEDG, 255-green);
  analogWrite(LEDB, 255-blue);
}