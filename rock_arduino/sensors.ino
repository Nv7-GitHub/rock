/*
Units
Acceleration: Gs
Velocity: m/s
Altitude: m
*/

#include <Adafruit_BMP280.h>
#include <Adafruit_BNO055.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setupSensors() {
  if (!bno.begin()) {
    Serial.println("Failed to initialize IMU");
    ledWrite(0, 255, 0);
    delay(1000);
  }
  if (!bmp.begin(0x76, 0x58)) {
    Serial.println("Failed to initialize pressure sensor");
    ledWrite(0, 255, 0);
    delay(1000);
  }
}

// Sensor values
float accelx, accely, accelz;
float gyrox, gyroy, gyroz;
float baroAlt;
float temp;
unsigned long lastRead = millis();
double dT;
bool readSensors() {
  imu::Quaternion quat = bno.getQuat();
  quat.x() = -quat.x();
  quat.y() = -quat.y();
  quat.z() = -quat.z();
  imu::Vector<3> linearaccel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> acc;
  // https://forums.adafruit.com/viewtopic.php?t=114125
  acc[0] = (1-2*(quat.y()*quat.y() + quat.z()*quat.z()))*linearaccel[0] +   (2*(quat.x()*quat.y() + quat.w()*quat.z()))*linearaccel[1] +   (2*(quat.x()*quat.z() - quat.w()*quat.y()))*linearaccel[2];  // rotate linearaccel by quaternion
  acc[1] =   (2*(quat.x()*quat.y() - quat.w()*quat.z()))*linearaccel[0] + (1-2*(quat.x()*quat.x() + quat.z()*quat.z()))*linearaccel[1] +   (2*(quat.y()*quat.z() + quat.w()*quat.x()))*linearaccel[2];
  acc[2] =   (2*(quat.x()*quat.z() + quat.w()*quat.y()))*linearaccel[0] +   (2*(quat.y()*quat.z() - quat.w()*quat.x()))*linearaccel[1] + (1-2*(quat.x()*quat.x() + quat.y()*quat.y()))*linearaccel[2];

  accelx = acc[0];
  accely = acc[1];
  accelz = acc[2];
  gyrox = gyro[0];
  gyroy = gyro[1];
  gyroz = gyro[2];

  // Temperature
  temp = bmp.readTemperature();

  // Barometer
  baroAlt = bmp.readAltitude(1013.25);

  // Calc dT
  unsigned long currentTime = millis();
  unsigned long deltaT = currentTime - lastRead;
  dT = ((double)deltaT) / 1000.0;
  lastRead = currentTime;

  return true;
}

//SimpleKalmanFilter altKf = SimpleKalmanFilter(0.04, 0.04, 0.01);
SimpleKalmanFilter velKf = SimpleKalmanFilter(0.03, 0.03, 0.01);

float lastAlt;

float accel; // Acceleration going up
float alt;
float vel;
float roll;
void predictPos() {
  accel = accelz;
  //alt = altKf.updateEstimate((double)baroAlt);
  alt = baroAlt;
  vel = velKf.updateEstimate((double)(alt - lastAlt) / dT); // TODO: Combine with accelz
  lastAlt = alt;
  roll = gyrox;
}

float recordingStartAlt = 0;
void sensorStartRecording() {
  recordingStartAlt = getAlt();
  lastAlt = getAlt();
}

float getAccel() {
  return accel;
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