#include <Arduino_BMI270_BMM150.h>
#include <Arduino_LPS22HB.h>

void setupSensors() {
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU")
  }
}

// To fill out other values
float buff;


// Sensor values
float accelx, accely, accelz;
float baroAlt;

bool readSensors() {
  if (!IMU.readAcceleration(accelx, accely, accelz)) {
    return false;
  }

  float pressure = BARO.readPressure();
  baroAlt = 44330 * (1 - pow(pressure/101.325, 1/5.255)); // https://docs.arduino.cc/tutorials/nano-33-ble-sense/barometric-sensor
}

float accel; // Acceleration going up
float alt;
void predictPos() {
  accel = accely; // TODO: Account for the angle of the rocket in this
  alt = baroAlt; // TODO: Use a 2d kalman filter to combine accel & baroAlt measurements
}

float getAccel() {
  return accel;
}

float getAlt() {
  return alt;
}