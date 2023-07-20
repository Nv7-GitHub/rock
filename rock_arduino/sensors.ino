/*
Units
Acceleration: Gs
Velocity: m/s
Altitude: m
*/

#include <Arduino_BMI270_BMM150.h>
#include <Arduino_LPS22HB.h>

void setupSensors() {
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
  }
}

// To fill out other values
float buff;


// Sensor values
float accelx, accely, accelz;
float baroAlt;
unsigned long lastRead = millis();
unsigned long dT;
bool readSensors() {
  if (!IMU.readAcceleration(accelx, accely, accelz)) {
    return false;
  }

  float pressure = BARO.readPressure();
  baroAlt = 44330 * (1 - pow(pressure/101.325, 1/5.255)); // https://docs.arduino.cc/tutorials/nano-33-ble-sense/barometric-sensor

  // Calc dT
  unsigned long currentTime = millis();
  dT = currentTime - lastRead;
  lastRead = currentTime;
}

float accel; // Acceleration going up
float alt;
float vel;
void predictPos() {
  vel = (baroAlt - alt) / (dT / 1000); // TODO: Use kalman filter to figure this out
  accel = accely; // TODO: Account for the angle of the rocket in this
  alt = baroAlt; // TODO: Use a 2d kalman filter to combine accel & baroAlt measurements
}

float getAccel() {
  return accel;
}

float getAlt() {
  return alt;
}

float getVel() {
  return vel;
}