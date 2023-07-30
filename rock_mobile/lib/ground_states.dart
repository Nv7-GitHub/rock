import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:provider/provider.dart';
import 'package:rock/state.dart';

class GroundPage extends StatefulWidget {
  const GroundPage({super.key});

  @override
  State<GroundPage> createState() => _GroundPageState();
}

class _GroundPageState extends State<GroundPage> {
  // Readonly
  late QualifiedCharacteristic _accelCharacteristic;
  late QualifiedCharacteristic _altCharacteristic;
  late QualifiedCharacteristic _velCharacteristic;
  double accel = 0;
  double alt = 0;
  double vel = 0;

  int s1 = 0;
  int s2 = 0;
  int s3 = 0;

  // Writable
  late QualifiedCharacteristic _servoCharacteristic;

  double floatFromBytes(List<int> data) {
    final bytes = Uint8List.fromList(data);
    final byteData = ByteData.sublistView(bytes);
    return byteData.getFloat32(0, Endian.little);
  }

  void accelListener(List<int> data) {
    setState(() {
      accel = floatFromBytes(data);
    });
  }

  void velListener(List<int> data) {
    setState(() {
      vel = floatFromBytes(data);
    });
  }

  void altListener(List<int> data) {
    setState(() {
      alt = floatFromBytes(data);
    });
  }

  void servoPositionsListener(List<int> data) {
    print("SERVO DATA: $data");
    final bytes = Uint8List.fromList(data);
    final byteData = ByteData.sublistView(bytes);
    setState(() {
      s1 = byteData.getInt32(0, Endian.little);
      s2 = byteData.getInt32(4, Endian.little);
      s3 = byteData.getInt32(8, Endian.little);
    });
  }

  int _lastServoWrite = DateTime.now().millisecondsSinceEpoch;
  void writeServoPositions() {
    int now = DateTime.now().millisecondsSinceEpoch;
    if (now - _lastServoWrite < 250) {
      Future.delayed(const Duration(milliseconds: 250)).then((v) {
        writeServoPositions();
      });
      return;
    }
    _lastServoWrite = now;

    final model = context.read<StateModel>();
    final bytes = Uint8List(12);
    final byteData = ByteData.sublistView(bytes);

    // Set 3 ints
    byteData.setInt32(0, s1, Endian.little);
    byteData.setInt32(4, s2, Endian.little);
    byteData.setInt32(8, s3, Endian.little);

    model.ble.writeCharacteristicWithResponse(_servoCharacteristic,
        value: bytes.toList());
  }

  void s1change(double v) {
    setState(() {
      s1 = v.toInt();
    });
    writeServoPositions();
  }

  void s2change(double v) {
    setState(() {
      s2 = v.toInt();
    });
    writeServoPositions();
  }

  void s3change(double v) {
    setState(() {
      s3 = v.toInt();
    });
    writeServoPositions();
  }

  void init() async {
    final model = context.read<StateModel>();
    _accelCharacteristic = QualifiedCharacteristic(
        characteristicId: deviceUuid("1000"),
        serviceId: deviceUuid("0000"),
        deviceId: model.deviceId!);
    _altCharacteristic = QualifiedCharacteristic(
        characteristicId: deviceUuid("1001"),
        serviceId: deviceUuid("0000"),
        deviceId: model.deviceId!);
    _velCharacteristic = QualifiedCharacteristic(
        characteristicId: deviceUuid("1002"),
        serviceId: deviceUuid("0000"),
        deviceId: model.deviceId!);
    _servoCharacteristic = QualifiedCharacteristic(
        characteristicId: deviceUuid("2000"),
        serviceId: deviceUuid("0000"),
        deviceId: model.deviceId!);

    // Read
    model.ble.readCharacteristic(_accelCharacteristic).then(accelListener);
    model.ble.readCharacteristic(_altCharacteristic).then(altListener);
    model.ble.readCharacteristic(_velCharacteristic).then(velListener);
    model.ble
        .readCharacteristic(_servoCharacteristic)
        .then(servoPositionsListener);

    // Subscribe
    model.ble
        .subscribeToCharacteristic(_accelCharacteristic)
        .listen(accelListener);
    model.ble.subscribeToCharacteristic(_altCharacteristic).listen(altListener);
    model.ble.subscribeToCharacteristic(_velCharacteristic).listen(velListener);
    // Can subscribe to servo pos but makes experience weird
  }

  @override
  void initState() {
    super.initState();
    init();
  }

  void armRocket() {
    StateModel model = context.read<StateModel>();
    model.writeDeviceState(DeviceState.ready);
    model.updateDeviceState(
        DeviceState.ready); // Needed because it won't update itself
    model.updateBleState(BLEState.disconnected);
  }

  @override
  Widget build(BuildContext context) {
    context.watch<StateModel>().checkRoute(context, "ground");

    return Scaffold(
      appBar: AppBar(
        title: const Text("ROCK on Ground"),
      ),
      body:
          ListView(scrollDirection: Axis.vertical, shrinkWrap: true, children: [
        ListTile(
          title: const Text("Acceleration"),
          subtitle: Text(accel.toString()),
        ),
        ListTile(
          title: const Text("Altitude"),
          subtitle: Text(alt.toString()),
        ),
        ListTile(
          title: const Text("Velocity"),
          subtitle: Text(vel.toString()),
        ),
        ListTile(
          title: const Text("Servo 1 Position"),
          subtitle: Slider(
            onChanged: s1change,
            max: 180,
            divisions: 180,
            value: s1.toDouble(),
            label: s1.toString(),
          ),
        ),
        ListTile(
          title: const Text("Servo 2 Position"),
          subtitle: Slider(
            onChanged: s2change,
            max: 180,
            divisions: 180,
            value: s2.toDouble(),
            label: s2.toString(),
          ),
        ),
        ListTile(
          title: const Text("Servo 3 Position"),
          subtitle: Slider(
            onChanged: s3change,
            max: 180,
            divisions: 180,
            value: s3.toDouble(),
            label: s3.toString(),
          ),
        ),
        FilledButton(
          onPressed: armRocket,
          child: const Text("Arm Rocket"),
        ),
      ]),
    );
  }
}

class ReadyPage extends StatefulWidget {
  const ReadyPage({super.key});

  @override
  State<ReadyPage> createState() => _ReadyPageState();
}

class _ReadyPageState extends State<ReadyPage> {
  void landedRocket() {
    StateModel model = context.read<StateModel>();
    model.updateDeviceState(DeviceState.none);
  }

  @override
  Widget build(BuildContext context) {
    context.watch<StateModel>().checkRoute(context, "ready");

    return Scaffold(
      appBar: AppBar(
        title: const Text("ROCK armed"),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Text(
                "Rocket is armed, press button below once rocket has landed and ready to transmit flight data"),
            FilledButton(
              onPressed: landedRocket,
              child: const Text("Receive Data"),
            ),
          ],
        ),
      ),
    );
  }
}
