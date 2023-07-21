import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:rock/ground_states.dart';
import 'package:rock/home.dart';
import 'package:rock/landed_state.dart';
import 'package:rock/state.dart';

void main() {
  runApp(
    ChangeNotifierProvider(
      create: (context) => StateModel(),
      child: const App(),
    ),
  );
}

class App extends StatelessWidget {
  const App({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'ROCK',
      theme: ThemeData(
        colorScheme: const ColorScheme.dark(),
        useMaterial3: true,
      ),
      routes: {
        '/': (context) => const ConnectPage(),
        '/none': (context) => const ConnectPage(),
        '/ground': (context) => const GroundPage(),
        '/ready': (context) => const ReadyPage(),
        '/landed': (context) => const LandedPage(),
      },
    );
  }
}
