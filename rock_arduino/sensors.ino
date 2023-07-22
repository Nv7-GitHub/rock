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

// Sensor values
float accelx, accely, accelz;
float gyrox, gyroy, gyroz;
float baroAlt;
unsigned long lastRead = millis();
unsigned long dT;
bool readSensors() {
  if (!IMU.readAcceleration(accelx, accely, accelz)) {
    return false;
  }
  if (!IMU.readGyroscope(gyrox, gyroy, gyroz)) {
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
float roll;
void predictPos() {
  vel = (baroAlt - alt) / (dT / 1000); // TODO: Use kalman filter to figure this out
  accel = accely; // TODO: Account for the angle of the rocket in this
  alt = baroAlt; // TODO: Use a 2d kalman filter to combine accel & baroAlt measurements
  roll += gyrox / (dT / 1000); // TODO: use kalman filter to figure this out
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