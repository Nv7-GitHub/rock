#include <Servo.h>

Servo S1;
Servo S2;
Servo S3;

void setupServos() {
  S1.attach(2);
  S2.attach(3);
  S3.attach(4);
}

void writeS1(int pos) {
  S1.write(pos);
}

void writeS2(int pos) {
  S2.write(pos);
}

void writeS3(int pos) {
  S3.write(pos);
}

int readS1() {
  return S1.read();
}

int readS2() {
  return S2.read();
}

int readS3() {
  return S3.read();
}