import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:rock/state.dart';

class GroundPage extends StatefulWidget {
  const GroundPage({super.key});

  @override
  State<GroundPage> createState() => _GroundPageState();
}

class _GroundPageState extends State<GroundPage> {
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
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // TODO: Implement real-time sensor data
            const Text(
                "Rocket is on ground, display the real-time sensor data here"),
            FilledButton(
              onPressed: armRocket,
              child: const Text("Arm Rocket"),
            ),
          ],
        ),
      ),
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
