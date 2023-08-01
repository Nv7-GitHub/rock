#include <Servo.h>

Servo S1;
Servo S2;
Servo S3;
int S1pos;
int S2pos;
int S3pos;

void setupServos() {
  S1.attach(2);
  S2.attach(3);
  S3.attach(4);
  writeS1(90);
  writeS2(90);
  writeS3(90);
}

void writeS1(int pos) {
  S1pos = pos;
  S1.write(pos);
}

void writeS2(int pos) {
  S2pos = pos;
  S2.write(pos);
}

void writeS3(int pos) {
  S3pos = pos;
  S3.write(pos);
}

int readS1() {
  return S1pos;
}

int readS2() {
  return S2pos;
}

int readS3() {
  return S3pos;
}