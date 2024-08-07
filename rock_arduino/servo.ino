#include <Servo.h>

Servo S1;
Servo S2;
Servo S3;
int S1pos;
int S2pos;
int S3pos;

const int S1Offset = 0;
const int S2Offset = 4; // 4 for flight comp 1, -4 for flight comp 2
const int S3Offset = -2; // -2 for both flight comps

void setupServos() {
  S1.attach(2, 900, 2100);
  S2.attach(3, 900, 2100);
  S3.attach(4, 900, 2100);
  writeS1(90);
  writeS2(90);
  writeS3(90);
}

void detachServos() {
  S1.detach();
  S2.detach();
  S3.detach();
}

int getUs(int pos) {
  return map(max(pos, 0), 0, 130, 900, 2100);
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