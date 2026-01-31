import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:colories_app/service/service.dart';

class TopCategoriesScreen extends StatefulWidget {
  
  const TopCategoriesScreen({super.key});
  @override
  State<TopCategoriesScreen> createState() => _TopCategoriesScreenState();
}


class _TopCategoriesScreenState extends State<TopCategoriesScreen> {

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
      appBar: AppBar(title: const Text('Top 3 Categories')),
      body: service.isLoading
          ? const Center(child: CircularProgressIndicator())
          : service.topCategories.isEmpty
              ? Center(
                  child: Text(service.isOffline
                      ? 'Offline: no data available'
                      : 'No data yet'),
                )
              : ListView.builder(
                  itemCount: service.topCategories.length,
                  itemBuilder: (_, index) {
                    final entry = service.topCategories[index];
                    return ListTile(
                      title: Text(entry.key),
                      trailing: Text('${entry.value.toStringAsFixed(0)} in ratings'),
                    );
                  },
                ),
    );
  }
}
