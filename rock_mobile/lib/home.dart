import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:provider/provider.dart';
import 'package:rock/state.dart';

class ConnectPage extends StatefulWidget {
  const ConnectPage({super.key});

  @override
  State<ConnectPage> createState() => _ConnectPageState();
}

class _ConnectPageState extends State<ConnectPage> {
  final serviceUuid = deviceUuid("0000");

  void init() async {
    // Scan
    final model = context.read<StateModel>();
    final scanResult = await model.ble.scanForDevices(
      withServices: [serviceUuid],
      scanMode: ScanMode.lowLatency,
      requireLocationServicesEnabled: false,
    ).first;

    // Connect
    model.updateBleState(BLEState.connecting);
    model.setDeviceId(scanResult.id);

    await model.ble.connectToDevice(
      id: scanResult.id,
      servicesWithCharacteristicsToDiscover: {
        serviceUuid: [],
      },
    ).listen((event) {
      if (event.connectionState == DeviceConnectionState.connected) {
        context.read<StateModel>().updateBleState(BLEState.connected);
      }
    }).asFuture();
  }

  @override
  void initState() {
    super.initState();
    init();
  }

  @override
  Widget build(BuildContext context) {
    context.read<StateModel>().checkRoute(context, "none");

    String text;
    switch (context.watch<StateModel>().bleState) {
      case BLEState.disconnected:
        text = "Searching for device";
        break;

      case BLEState.connecting:
        text = "Connecting to device";
        break;

      case BLEState.connected:
        text = "Detecting device state";
        break;
    }

    return Scaffold(
      appBar: AppBar(
        title: const Text("ROCK Disconnected"),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            const Spacer(flex: 20),
            const CircularProgressIndicator(),
            const Spacer(flex: 2),
            Text(text),
            const Spacer(flex: 20),
          ],
        ),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }
}
