import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:rock/state.dart';

class LandedPage extends StatefulWidget {
  const LandedPage({super.key});

  @override
  State<LandedPage> createState() => _LandedPageState();
}

class _LandedPageState extends State<LandedPage> {
  // TODO: Receive data from rocket

  @override
  Widget build(BuildContext context) {
    context.watch<StateModel>().checkRoute(context, "landed");

    return Scaffold(
      appBar: AppBar(
        title: const Text("ROCK has landed"),
      ),
      body: const Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Spacer(flex: 20),
            CircularProgressIndicator(),
            Spacer(flex: 2),
            Text("Receiving flight data"),
            Spacer(flex: 20),
          ],
        ),
      ),
    );
  }
}
