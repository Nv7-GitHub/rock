/*
Units
Acceleration: Gs
Velocity: m/s
Altitude: m
*/

#include <Arduino_BMI270_BMM150.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_HS300x.h>
#include <SimpleKalmanFilter.h>

void setupSensors() {
  if (!IMU.begin()) {
    #ifdef DEBUG
    Serial.println("Failed to initialize IMU");
    #endif
  }
  if (!HS300x.begin()) {
    #ifdef DEBUG
    Serial.println("Failed to initialize temperature sensor");
    #endif
  }
  if (!BARO.begin()) {
    #ifdef DEBUG
    Serial.println("Failed to initialize pressure sensor");
    #endif
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
  if (!IMU.readAcceleration(accelx, accely, accelz)) {
    #ifdef DEBUG
    Serial.println("Failed to read IMU");
    #endif
    return false;
  }
  if (!IMU.readGyroscope(gyrox, gyroy, gyroz)) {
    #ifdef DEBUG
    Serial.println("Failed to read IMU");
    #endif
    return false;
  }

  // Temperature
  temp = HS300x.readTemperature();

  // Barometer
  float pressure = BARO.readPressure();
  baroAlt = 44330 * (1 - pow(pressure/101.325, 1/5.255)); // https://docs.arduino.cc/tutorials/nano-33-ble-sense/barometric-sensor

  // Calc dT
  unsigned long currentTime = millis();
  unsigned long deltaT = currentTime - lastRead;
  dT = ((double)deltaT) / 1000.0;
  lastRead = currentTime;

  return true;
}

SimpleKalmanFilter altKf = SimpleKalmanFilter(0.05, 0.05, 0.01);
SimpleKalmanFilter velKf = SimpleKalmanFilter(0.05, 0.05, 0.01);

float lastAlt;

float accel; // Acceleration going up
float alt;
float vel;
float roll;
void predictPos() {
  accel = accelx + 1; // Account for grav
  alt = altKf.updateEstimate((double)baroAlt);
  vel = velKf.updateEstimate((double)(alt - lastAlt) / dT);
  lastAlt = alt;
  roll = gyrox;
}

float recordingStartAlt = 0;
void sensorStartRecording() {
  recordingStartAlt = getAlt();
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