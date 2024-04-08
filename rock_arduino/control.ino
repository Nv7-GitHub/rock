#include "profile.h"

float target; // Input
float angle;

const float Kp = 7; // Use 10 if mass is 560ish
const float Ki = 0;
const float Kd = 0;

int timeIndex = 0;

float integral = 0;
float prevE = 0;
extern double dT;
unsigned long controlStartTime = 0;
void resetControl() {
  controlStartTime = flightTime();
  prevE = 0;
  integral = 0;
}

void loopControl() {
  // Get input
  float currTime = ((float)(flightTime() - controlStartTime))/1000.0;
  while (targetTime[timeIndex] < currTime && timeIndex < sizeof(targetTime)/sizeof(float) - 1) {
    timeIndex++;
  }
  target = targetAlt[timeIndex];
  float e = getAlt() - target;
  if (currTime < 3) {
    e = 0; // ENABLE after 3 seconds
  }

  // Calculate PID
  float p = Kp * e;
  integral += Ki * e * dT;
  float d = (Kd * (e - prevE))/dT;
  float angle = p + integral + d;
  if (angle < 0) {
    angle = 0;
  } else if (angle > 75) {
    angle = 75;
  }

  // Write servos
  writeS2((int)(90.0-angle));
  writeS3((int)(90.0-angle));

  // Store for next iter
  prevE = e;
}