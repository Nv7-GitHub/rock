#include <ArduinoBLE.h>

#define BLE_UUID(ind) ("e7cce444-" ind "-4260-81de-7a42c1378923")

BLEService service(BLE_UUID("0000"));
BLEByteCharacteristic stateCharacteristic(BLE_UUID("0001"), BLERead | BLENotify);
BLEFloatCharacteristic accelCharacteristic(BLE_UUID("1000"), BLERead);
BLEFloatCharacteristic altCharacteristic(BLE_UUID("1001"), BLERead);
BLEFloatCharacteristic velCharacteristic(BLE_UUID("1002"), BLERead);
BLECharacteristic servoPositions(BLE_UUID("2000"), BLENotify, sizeof(int) * 3); // 3 x int

void setupBle() {
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE");
  }
  BLE.setLocalName("ROCK");
  BLE.setDeviceName("ROCK");
  BLE.setAdvertisedService(service);
  
  service.addCharacteristic(stateCharacteristic);
  service.addCharacteristic(accelCharacteristic);
  service.addCharacteristic(altCharacteristic);
  service.addCharacteristic(velCharacteristic);
  service.addCharacteristic(servoPositions);

  stateCharacteristic.writeValue(getState());
  accelCharacteristic.writeValue(0);
  altCharacteristic.writeValue(0);
  velCharacteristic.writeValue(0);

  BLE.addService(service);
  BLE.advertise();
}

void bleWriteState() {
  stateCharacteristic.writeValue(getState());
}

void bleReadState() {
  if (stateCharacteristic.written()) {
    setState(stateCharacteristic.value());
  }
}

void bleWriteSensors() {
  accelCharacteristic.writeValue(getAccel());
  altCharacteristic.writeValue(getAlt());
  velCharacteristic.writeValue(getVel());
}

void bleServoPositionsRead() {
  if (servoPositions.written()) {
    int* positions = (int*)servoPositions.value();
    writeS1(positions[0]);
    writeS2(positions[1]);
    writeS3(positions[2]);
  }
}