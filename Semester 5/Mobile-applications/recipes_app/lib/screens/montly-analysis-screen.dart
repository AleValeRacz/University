import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:colories_app/service/service.dart';

class MonthlyAnalysisScreen extends StatefulWidget {
  const MonthlyAnalysisScreen({super.key});

  @override
  State<MonthlyAnalysisScreen> createState() => _MonthlyAnalysisScreenState();
}

class _MonthlyAnalysisScreenState extends State<MonthlyAnalysisScreen> {

   @override
  void initState() {
    super.initState();
    WidgetsBinding.instance.addPostFrameCallback((_) {
      final service = context.read<RecipeService>();
      service.ComputeMonthlyAverages();
    });
  }
  @override
  Widget build(BuildContext context) {
    final service = context.watch<RecipeService>();

    return Scaffold(
      appBar: AppBar(title: const Text('Monthly Ratings Analysis')),
      body: service.isLoading
          ? const Center(child: CircularProgressIndicator())
          : service.monthlyAverages.isEmpty
              ? Center(
                  child: Text(service.isOffline
                      ? 'Offline: no data available'
                      : 'No data yet'),
                )
              : ListView.builder(
                  itemCount: service.monthlyAverages.length,
                  itemBuilder: (_, index) {
                    final month = service.monthlyAverages.keys.elementAt(index);
                    final total = service.monthlyAverages[month]!;
                    return ListTile(
                      title: Text(month),
                      trailing: Text('${total.toStringAsFixed(2)} average score'),
                    );
                  },
                ),
    );
  }
}
