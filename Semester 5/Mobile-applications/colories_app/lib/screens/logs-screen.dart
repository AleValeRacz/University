import 'package:colories_app/service/service.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:go_router/go_router.dart';

class LogsScreen extends StatefulWidget {
  const LogsScreen({super.key});

  @override
  State<LogsScreen> createState() => _LogsScreenState();
}

class _LogsScreenState extends State<LogsScreen> {
  @override
  void initState() {
    super.initState();

    final service = context.read<LogService>();
    service.newLogStream.listen((log) {
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(
          content: Text('New log added: ${log.amount} kcal (${log.category})'),
        ),
      );
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Calorie Logs')),
      body: Consumer<LogService>(
        builder: (_, service, __) {
          if (service.isLoading) {
            return const Center(child: CircularProgressIndicator());
          }

          if (service.logs.isEmpty) {
            return Center(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  const Text('No logs found'),
                  if (service.isOffline) ...[
                    const SizedBox(height: 8),
                    const Text('Offline mode'),
                    TextButton(
                      onPressed: service.loadLogs,
                      child: const Text('Retry'),
                    ),
                  ],
                ],
              ),
            );
          }

          return Stack(
            children: [
              Column(
                children: [
                  Padding(
                    padding: const EdgeInsets.all(8),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      children: [
                        ElevatedButton(
                          onPressed: service.isOffline
                              ? null
                              : () => context.push('/monthly-analysis'),
                          child: const Text('Monthly Analysis'),
                        ),
                        ElevatedButton(
                          onPressed: service.isOffline
                              ? null
                              : () => context.push('/top-categories'),
                          child: const Text('Top Categories'),
                        ),
                      ],
                    ),
                  ),

                  Expanded(
                    child: RefreshIndicator(
                      onRefresh: service.loadLogs,
                      child: ListView.builder(
                        padding: const EdgeInsets.all(8),
                        itemCount: service.logs.length,
                        itemBuilder: (context, index) {
                          final log = service.logs[index];

                          return Card(
                            margin: const EdgeInsets.symmetric(vertical: 6),
                            child: InkWell(
                              onTap: () => context.push('/log/${log.id}'),
                              child: Padding(
                                padding: const EdgeInsets.all(12),
                                child: Column(
                                  crossAxisAlignment: CrossAxisAlignment.start,
                                  children: [
                                    Row(
                                      mainAxisAlignment:
                                          MainAxisAlignment.spaceBetween,
                                      children: [
                                        Text(
                                          '${log.amount.toStringAsFixed(0)} kcal',
                                          style: const TextStyle(
                                            fontSize: 18,
                                            fontWeight: FontWeight.bold,
                                          ),
                                        ),
                                        IconButton(
                                          icon: const Icon(Icons.delete),
                                          onPressed: service.isOffline
                                              ? null
                                              : () async {
                                                  final confirm =
                                                      await showDialog<bool>(
                                                        context: context,
                                                        builder: (_) => AlertDialog(
                                                          title: const Text(
                                                            'Delete log',
                                                          ),
                                                          content: const Text(
                                                            'Are you sure?',
                                                          ),
                                                          actions: [
                                                            TextButton(
                                                              onPressed: () =>
                                                                  Navigator.pop(
                                                                    context,
                                                                    false,
                                                                  ),
                                                              child: const Text(
                                                                'Cancel',
                                                              ),
                                                            ),
                                                            TextButton(
                                                              onPressed: () =>
                                                                  Navigator.pop(
                                                                    context,
                                                                    true,
                                                                  ),
                                                              child: const Text(
                                                                'Delete',
                                                              ),
                                                            ),
                                                          ],
                                                        ),
                                                      );

                                                  if (confirm == true) {
                                                    final success =
                                                        await service.deleteLog(
                                                          log.id,
                                                        );
                                                    if (!success) {
                                                      ScaffoldMessenger.of(
                                                        context,
                                                      ).showSnackBar(
                                                        const SnackBar(
                                                          content: Text(
                                                            'Failed to delete log (server error)',
                                                          ),
                                                          backgroundColor:
                                                              Colors.red,
                                                        ),
                                                      );
                                                    }
                                                  }
                                                },
                                        ),
                                      ],
                                    ),
                                    const SizedBox(height: 6),
                                    Text(
                                      'Category: ${log.category}',
                                      style: TextStyle(
                                        color: Colors.grey.shade700,
                                      ),
                                    ),
                                    Text(
                                      'Date: ${log.date.toLocal().toIso8601String().split('T').first}',
                                      style: TextStyle(
                                        color: Colors.grey.shade700,
                                      ),
                                    ),
                                  ],
                                ),
                              ),
                            ),
                          );
                        },
                      ),
                    ),
                  ),
                ],
              ),

              if (service.isOperationInProgress) ...[
                const Opacity(
                  opacity: 0.6,
                  child: ModalBarrier(dismissible: false, color: Colors.black),
                ),
                const Center(child: CircularProgressIndicator()),
              ],
            ],
          );
        },
      ),

      floatingActionButton: FloatingActionButton(
        onPressed: context.watch<LogService>().isOffline
            ? null
            : () => context.push('/add'),
        child: const Icon(Icons.add),
      ),
    );
  }
}
