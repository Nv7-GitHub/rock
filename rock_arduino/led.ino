#define RED 22     
#define BLUE 24     
#define GREEN 23

void setupLed() {
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
}

void ledWrite(bool red, bool blue, bool green, bool builtin) {
  if (red) {
    digitalWrite(RED, LOW);
  } else {
    digitalWrite(RED, HIGH);
  }

  if (blue) {
    digitalWrite(BLUE, HIGH);
  } else {
    digitalWrite(BLUE, LOW);
  }

  if (green) {
    digitalWrite(GREEN, HIGH);
  } else {
    digitalWrite(GREEN, LOW);
  }

  if (builtin) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }
}