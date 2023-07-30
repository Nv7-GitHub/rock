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

  // Writable
  late QualifiedCharacteristic _servoCharacteristic;

  double floatFromBytes(List<int> data) {
    final bytes = Uint8List.fromList(data);
    final byteData = ByteData.sublistView(bytes);
    return byteData.getFloat32(0);
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

    // Read
    model.ble.readCharacteristic(_accelCharacteristic).then(accelListener);
    model.ble.readCharacteristic(_altCharacteristic).then(altListener);
    model.ble.readCharacteristic(_velCharacteristic).then(velListener);

    // Subscribe
    model.ble
        .subscribeToCharacteristic(_accelCharacteristic)
        .listen(accelListener);
    model.ble.subscribeToCharacteristic(_altCharacteristic).listen(altListener);
    model.ble.subscribeToCharacteristic(_velCharacteristic).listen(velListener);
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
