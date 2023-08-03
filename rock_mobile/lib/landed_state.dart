import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:provider/provider.dart';
import 'package:rock/state.dart';

class LandedPage extends StatefulWidget {
  const LandedPage({super.key});

  @override
  State<LandedPage> createState() => _LandedPageState();
}

class DataFrame {
  late int time;
  late int state;
  late double accel;
  late double vel;
  late double alt;
  late double roll;
  late int s1;
  late int s2;
  late int s3;
  late double ax;
  late double ay;
  late double az;
  late double gx;
  late double gy;
  late double gz;
  late double baro;
  late double temp;

  DataFrame.fromBuffer(List<int> buff) {
    final bytes = Uint8List.fromList(buff);
    final byteData = ByteData.sublistView(bytes);
    time = byteData.getInt32(0, Endian.little);
    state = byteData.getInt32(4, Endian.little);
    accel = byteData.getFloat32(8, Endian.little);
    vel = byteData.getFloat32(12, Endian.little);
    alt = byteData.getFloat32(16, Endian.little);
    roll = byteData.getFloat32(20, Endian.little);
    s1 = byteData.getInt32(24, Endian.little);
    s2 = byteData.getInt32(28, Endian.little);
    s3 = byteData.getInt32(32, Endian.little);
    ax = byteData.getFloat32(36, Endian.little);
    ay = byteData.getFloat32(40, Endian.little);
    az = byteData.getFloat32(44, Endian.little);
    gx = byteData.getFloat32(48, Endian.little);
    gy = byteData.getFloat32(52, Endian.little);
    gz = byteData.getFloat32(56, Endian.little);
    baro = byteData.getFloat32(60, Endian.little);
    temp = byteData.getFloat32(64, Endian.little);
  }
}

class _LandedPageState extends State<LandedPage> {
  late QualifiedCharacteristic _readFrameCharacteristic;
  late QualifiedCharacteristic _frameCharacteristic;
  int receivedFrames = 0;
  int frameCount = 0;
  List<DataFrame> frames = [];

  void readFrameListener(List<int> data) {
    print("RECEIVED READ FRAME: $data");
    if (receivedFrames == 0) {
      // Receive frame count
      final bytes = Uint8List.fromList(data);
      final byteData = ByteData.sublistView(bytes);
      int frameCountRaw = byteData.getInt32(0, Endian.little);
      if (frameCountRaw == 0) {
        return;
      }
      setState(() {
        receivedFrames = 1;
        frameCount = frameCountRaw;
      });

      // Acknowledge frame count
      final model = context.read<StateModel>();
      print("WRITE TO BLE, count: $frameCountRaw");
      model.ble.writeCharacteristicWithResponse(_readFrameCharacteristic,
          value: [0, 0, 0, 1]);
    }
  }

  void frameListener(List<int> data) {
    print("RECEIVED FRAME: $data");
    final frame = DataFrame.fromBuffer(data); // Parse frame

    // Acknowledge frame
    final bytes = Uint8List(12);
    final byteData = ByteData.sublistView(bytes);
    byteData.setInt32(0, frame.time, Endian.little);
    final model = context.read<StateModel>();
    model.ble.writeCharacteristicWithResponse(_readFrameCharacteristic,
        value: bytes.toList());

    // Display
    setState(() {
      frames.add(frame);
      receivedFrames++;

      if (receivedFrames - 1 == frameCount) {
        // TODO: Save frames
        print("RECEIVED FRAMES: $frames");
      }
    });
  }

  void init() async {
    final model = context.read<StateModel>();
    _readFrameCharacteristic = QualifiedCharacteristic(
        characteristicId: deviceUuid("3000"),
        serviceId: deviceUuid("0000"),
        deviceId: model.deviceId!);
    _frameCharacteristic = QualifiedCharacteristic(
        characteristicId: deviceUuid("3001"),
        serviceId: deviceUuid("0000"),
        deviceId: model.deviceId!);

    model.ble
        .readCharacteristic(_readFrameCharacteristic)
        .then(readFrameListener);

    model.ble
        .subscribeToCharacteristic(_readFrameCharacteristic)
        .listen(readFrameListener);
    model.ble
        .subscribeToCharacteristic(_frameCharacteristic)
        .listen(frameListener);
  }

  @override
  void initState() {
    super.initState();
    init();
  }

  @override
  Widget build(BuildContext context) {
    context.watch<StateModel>().checkRoute(context, "landed");

    return Scaffold(
      appBar: AppBar(
        title: const Text("ROCK has landed"),
      ),
      body: Center(
        child: Column(mainAxisAlignment: MainAxisAlignment.center, children: [
          const Spacer(flex: 20),
          frameCount == 0
              ? const CircularProgressIndicator()
              : CircularProgressIndicator(
                  value: (receivedFrames - 1) / frameCount,
                ),
          const Spacer(flex: 2),
          const Text("Receiving flight data"),
          const Spacer(flex: 20),
        ]),
      ),
    );
  }
}
