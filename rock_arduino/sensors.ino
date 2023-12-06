/*
Units
Acceleration: Gs
Velocity: m/s
Altitude: m
*/

#include <Adafruit_BMP280.h>
#include <Adafruit_BNO055.h>
#include <SimpleKalmanFilter.h>
#include "LSM9DS1.h"

Adafruit_BMP280 bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

void setupSensors() {
  if (!bno.begin()) {
    setupError("Failed to initialize gyro");
  }
  if (!bmp.begin(0x76, 0x58)) {
    setupError("Failed to initialize barometer");
  }
  if (!IMU.begin()) {
    setupError("Failed to initialize accelerometer");
  }
}

// Sensor values
const float MAX_ACCEL = 16 * 9.81;
const float MAX_JERK_INST = 35; // Maximum change of acceleration over a iteration

float accelx, accely, accelz;
float gyrox, gyroy, gyroz;
float baroAlt;
float temp;
unsigned long lastRead = millis();
double dT;
bool readSensors() {
  float rawaccx;
  float rawaccy;
  float rawaccz;
  if (IMU.accelerationAvailable()) {
    imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    IMU.readAcceleration(rawaccy, rawaccx, rawaccz);
    rawaccx *= -9.81;
    rawaccy *= -9.81;
    rawaccz *= 9.81;
    rawaccx -= gravity[0];
    rawaccy -= gravity[1];
    rawaccz -= gravity[2];
  }

  imu::Quaternion quat = bno.getQuat();
  quat.x() = -quat.x();
  quat.y() = -quat.y();
  quat.z() = -quat.z();
  //imu::Vector<3> linearaccel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> linearaccel = imu::Vector<3>(rawaccx, rawaccy, rawaccz);
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> acc;
  // https://forums.adafruit.com/viewtopic.php?t=114125
  acc[0] = (1-2*(quat.y()*quat.y() + quat.z()*quat.z()))*linearaccel[0] +   (2*(quat.x()*quat.y() + quat.w()*quat.z()))*linearaccel[1] +   (2*(quat.x()*quat.z() - quat.w()*quat.y()))*linearaccel[2];  // rotate linearaccel by quaternion
  acc[1] =   (2*(quat.x()*quat.y() - quat.w()*quat.z()))*linearaccel[0] + (1-2*(quat.x()*quat.x() + quat.z()*quat.z()))*linearaccel[1] +   (2*(quat.y()*quat.z() + quat.w()*quat.x()))*linearaccel[2];
  acc[2] =   (2*(quat.x()*quat.z() + quat.w()*quat.y()))*linearaccel[0] +   (2*(quat.y()*quat.z() - quat.w()*quat.x()))*linearaccel[1] + (1-2*(quat.x()*quat.x() + quat.y()*quat.y()))*linearaccel[2];

  if (abs(acc[0]) < MAX_ACCEL && abs(acc[1]) < MAX_ACCEL && abs(acc[2]) < MAX_ACCEL && abs(acc[0] - accelx) < MAX_JERK_INST && abs(acc[1] - accelx) < MAX_JERK_INST && abs(acc[2] - accelx) < MAX_JERK_INST) { // Why does this happen?
    accelx = acc[0];
    accely = acc[1];
    accelz = acc[2];
  }
  gyrox = gyro[0];
  gyroy = gyro[1];
  gyroz = gyro[2];

  // Temperature
  temp = bmp.readTemperature();

  // Barometer
  baroAlt = bmp.readAltitude(1017.14);

  // Calc dT
  unsigned long currentTime = millis();
  unsigned long deltaT = currentTime - lastRead;
  dT = ((double)deltaT) / 1000.0;
  lastRead = currentTime;

  return true;
}

SimpleKalmanFilter altKf = SimpleKalmanFilter(0.04, 0.04, 0.01);

float accel; // Acceleration going up
float alt;
float vel = 0; // Vel going up
float roll;
void predictPos() {
  accel = accelz;
  alt = altKf.updateEstimate((double)baroAlt);
  vel += (accelz * dT);
  roll = gyrox;
}

float recordingStartAlt = 0;
void sensorStartRecording() {
  recordingStartAlt = getAlt();
  vel = 0;
}

float getAccel() {
  return accel;
}

float getTotalAccel() {
  return abs(accelx) + abs(accely) + abs(accelz);
}

float getAlt() {
  return alt - recordingStartAlt;
}

float getVel() {
  return vel;
}

float getRoll() {
  return roll;
}

float getTemp() {
  return temp;
}