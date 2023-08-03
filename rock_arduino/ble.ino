#include <ArduinoBLE.h>

#define BLE_UUID(ind) ("e7cce444-" ind "-4260-81de-7a42c1378923")

BLEService service(BLE_UUID("0000"));
BLEByteCharacteristic stateCharacteristic(BLE_UUID("0001"), BLERead | BLENotify | BLEWrite);
BLEFloatCharacteristic accelCharacteristic(BLE_UUID("1000"), BLERead | BLENotify);
BLEFloatCharacteristic altCharacteristic(BLE_UUID("1001"), BLERead | BLENotify);
BLEFloatCharacteristic velCharacteristic(BLE_UUID("1002"), BLERead | BLENotify);
BLECharacteristic servoPositions(BLE_UUID("2000"), BLENotify | BLEWrite | BLERead, sizeof(int) * 3); // 3 x int
BLEIntCharacteristic readFrames(BLE_UUID("3000"), BLENotify | BLEWrite | BLERead);
extern const int FRAME_SIZE;
BLECharacteristic frame(BLE_UUID("3001"), BLENotify | BLERead, FRAME_SIZE);

void setupBle() {
  if (!BLE.begin()) {
    #ifdef DEBUG
    Serial.println("Failed to initialize BLE");
    #endif
  }
  BLE.setLocalName("ROCK");
  BLE.setDeviceName("ROCK");
  BLE.setAdvertisedService(service);
  
  service.addCharacteristic(stateCharacteristic);
  service.addCharacteristic(accelCharacteristic);
  service.addCharacteristic(altCharacteristic);
  service.addCharacteristic(velCharacteristic);
  service.addCharacteristic(servoPositions);
  service.addCharacteristic(readFrames);
  service.addCharacteristic(frame);

  stateCharacteristic.writeValue(getState());
  accelCharacteristic.writeValue(0);
  altCharacteristic.writeValue(0);
  velCharacteristic.writeValue(0);
  readFrames.writeValue(0);

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

  // Servo positions
  int servoPos[3] = {readS1(), readS2(), readS3()};
  servoPositions.writeValue(servoPos, sizeof(servoPos));
}

void bleServoPositionsRead() {
  if (servoPositions.written()) {
    int* positions = (int*)servoPositions.value();
    writeS1(positions[0]);
    writeS2(positions[1]);
    writeS3(positions[2]);
  }
}