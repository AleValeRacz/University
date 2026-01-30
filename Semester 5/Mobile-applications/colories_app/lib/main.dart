import 'package:colories_app/screens/add-log-screen.dart';
import 'package:colories_app/screens/logs-screen.dart';
import 'package:colories_app/screens/montly-analysis-screen.dart';
import 'package:colories_app/screens/top-categories-screen.dart';
import 'package:colories_app/screens/view-log-screen.dart';
import 'package:colories_app/service/service.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:go_router/go_router.dart';
void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  final service = LogService();

  final router = GoRouter(
    routes: [
      GoRoute(
        path: '/',
        builder: (context, state) => LogsScreen(),
      ),
      GoRoute(
        path: '/add',
        builder: (context, state) => AddLogScreen(),
       ),
      GoRoute(
        path: '/log/:id',
        builder: (context, state) {
          final id = int.parse(state.pathParameters['id']!);
          return ViewLogScreen(logId: id);
        },

      ),
       GoRoute(
        path: '/monthly-analysis',
        builder: (context, state) => MonthlyAnalysisScreen(),
       ),
        GoRoute(
        path: '/top-categories',
        builder: (context, state) => TopCategoriesScreen(),
       ),
    ],
  );


  runApp(
     ChangeNotifierProvider(
      create: (_) => service,
      child: MyApp(router: router),
    ),
  );
}

class MyApp extends StatelessWidget {
  final GoRouter router;
  const MyApp({super.key, required this.router});

  @override
  Widget build(BuildContext context) {
     return MaterialApp.router(
      title: 'App',
      routerConfig: router,
    );
  }

}
