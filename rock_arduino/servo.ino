#include <Servo.h>

Servo S1;
Servo S2;
Servo S3;
int S1pos;
int S2pos;
int S3pos;

const int S1Offset = 0;
const int S2Offset = -2;
const int S3Offset = -11;

void setupServos() {
  S1.attach(2, 900, 2100);
  S2.attach(3, 900, 2100);
  S3.attach(4, 900, 2100);
  writeS1(90);
  writeS2(90);
  writeS3(90);
}

int getUs(int pos) {
  return map(pos, 0, 180, 900, 2100);
}

void writeS1(int pos) {
  S1pos = pos;
  S1.writeMicroseconds(getUs(pos + S1Offset));
}

void writeS2(int pos) {
  S2pos = pos;
  S2.writeMicroseconds(getUs(pos + S2Offset));
}

void writeS3(int pos) {
  S3pos = pos;
  S3.writeMicroseconds(getUs(pos + S3Offset));
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