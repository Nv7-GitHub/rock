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
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

void setupSensors() {
  if (!bno.begin()) {
    setupError("Failed to initialize IMU");
  }
  if (!bmp.begin(0x76, 0x58)) {
    setupError("Failed to initialize barometer");
  }
}

// Sensor values
float grav;
float accelx, accely, accelz;
float gyrox, gyroy, gyroz;
float baroAlt;
float temp;
unsigned long lastRead = millis();
double dT;
void readSensors() {
  imu::Quaternion quat = bno.getQuat();
  quat.x() = -quat.x();
  quat.y() = -quat.y();
  quat.z() = -quat.z();
  imu::Vector<3> linearaccel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> gravimu = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY); // For ready detect
  grav = gravimu.y();
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
  baroAlt = bmp.readAltitude(1017.14);

  // Calc dT
  unsigned long currentTime = millis();
  unsigned long deltaT = currentTime - lastRead;
  dT = ((double)deltaT) / 1000.0;
  lastRead = currentTime;
}

SimpleKalmanFilter altKf = SimpleKalmanFilter(0.04, 0.04, 0.01);

float lastAlt;

float accel; // Acceleration going up
float alt;
float vel; // Vel going up
float roll;
void predictPos() {
  accel = accelz;
  alt = altKf.updateEstimate((double)baroAlt);
  if (flightTime() < 1000) {
    vel = 82.5; // Actual value: 92.14612321670953 (I made it a little lower because its better to under-correct than over-correct), in the future when have 16g accelerometer this can go away
    // Use vel = 89 for flight comp 2
  } else {
    vel += accelz * dT;
  }
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

float getGrav() {
  return grav;
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