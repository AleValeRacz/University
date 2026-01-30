import 'package:colories_app/model/log.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:colories_app/service/service.dart';

class ViewLogScreen extends StatelessWidget {
  final int logId;

  const ViewLogScreen({super.key, required this.logId});

  @override
  Widget build(BuildContext context) {
    return FutureBuilder<Log?>(
      future: context.read<LogService>().getLogDetails(logId),
      builder: (context, snapshot) {
        if (snapshot.connectionState == ConnectionState.waiting) {
          return const Scaffold(
            body: Center(child: CircularProgressIndicator()),
          );
        }

        if (!snapshot.hasData) {
          return const Scaffold(
            body: Center(child: Text('Log not found')),
          );
        }

        final log = snapshot.data!;
        return Scaffold(
          appBar: AppBar(title: const Text('Log Details')),
          body: Padding(
            padding: const EdgeInsets.all(16),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text('Amount: ${log.amount} kcal'),
                Text('Date: ${log.date.toLocal()}'),
                Text('Category: ${log.category}'),
                Text('Type: ${log.type}'),
                Text('Description: ${log.description}'),
              ],
            ),
          ),
        );
      },
    );
  }
}
