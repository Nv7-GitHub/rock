import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';

enum BLEState {
  disconnected,
  connecting,
  connected,
}

Uuid deviceUuid(String ind) {
  return Uuid.parse("e7cce444-$ind-4260-81de-7a42c1378923");
}

enum DeviceState {
  ground,
  ready,
  ascent,
  apogee,
  descent,
  landed,

  // Not on device
  none,
}

class StateModel extends ChangeNotifier {
  BLEState bleState = BLEState.disconnected;
  String? deviceId;
  final ble = FlutterReactiveBle();

  late QualifiedCharacteristic _stateCharacteristic;
  DeviceState deviceState = DeviceState.none;

  void updateBleState(BLEState newState) {
    bleState = newState;
    notifyListeners();
  }

  void checkRoute(BuildContext context, String route) {
    if (route != deviceState.name) {
      Navigator.popAndPushNamed(context, deviceState.name);
    }
  }

  void updateDeviceState(DeviceState state) {
    deviceState = state;
    notifyListeners();
  }

  void writeDeviceState(DeviceState state) {
    ble.writeCharacteristicWithResponse(_stateCharacteristic,
        value: [state.index]);
  }

  void setDeviceId(String id) {
    deviceId = id;

    // Listen to state
    _stateCharacteristic = QualifiedCharacteristic(
        characteristicId: deviceUuid("0001"),
        serviceId: deviceUuid("0000"),
        deviceId: deviceId!);
    ble.subscribeToCharacteristic(_stateCharacteristic).listen((data) {
      deviceState = DeviceState.values[data[0]];
      notifyListeners();
    });

    notifyListeners();
  }
}
