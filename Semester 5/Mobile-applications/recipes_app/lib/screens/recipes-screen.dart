import 'package:colories_app/service/service.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:go_router/go_router.dart';

class RecipesScreen extends StatefulWidget {
  const RecipesScreen({super.key});

  @override
  State<RecipesScreen> createState() => _RecipesScreenState();
}

class _RecipesScreenState extends State<RecipesScreen> {
  @override
  void initState() {
    super.initState();

    final service = context.read<RecipeService>();
    service.newLogStream.listen((recipe) {
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(
          content: Text('New recipe added: ${recipe.title} , ${recipe.category}'),
        ),
      );
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Recipes List')),
      body: Consumer<RecipeService>(
        builder: (_, service, __) {
          if (service.isLoading) {
            return const Center(child: CircularProgressIndicator());
          }

          if (service.recipes.isEmpty) {
            return Center(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  const Text('No recipe found'),
                  if (!service.isdataLoaded) ...[
                    const SizedBox(height: 8),
                       if (service.isOffline) const Text('Offline mode'),
                    TextButton(
                      onPressed: () async => await service.loadRecipes(forceServer: true),
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
                          onPressed: /*service.isOffline
                              ? null
                              : */ () => context.push('/monthly-analysis'),
                          child: const Text('Monthly Analysis'),
                        ),
                        ElevatedButton(
                          onPressed: /*service.isOffline
                              ? null
                              : */ () => context.push('/top-categories'),
                          child: const Text('Top Categories'),
                        ),
                      ],
                    ),
                  ),

                  Expanded(
                    child: RefreshIndicator(
                      onRefresh: service.loadRecipes,
                      child: ListView.builder(
                        padding: const EdgeInsets.all(8),
                        itemCount: service.recipes.length,
                        itemBuilder: (context, index) {
                          final recipe = service.recipes[index];

                          return Card(
                            margin: const EdgeInsets.symmetric(vertical: 6),
                            child: InkWell(
                              onTap: () => context.push('/recipe/${recipe.id}'),
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
                                          recipe.title,
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
                                                            'Delete recipe',
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
                                                        await service.deleteRecipe(
                                                          recipe.id,
                                                        );
                                                    if (!success) {
                                                      ScaffoldMessenger.of(
                                                        context,
                                                      ).showSnackBar(
                                                        const SnackBar(
                                                          content: Text(
                                                            'Failed to delete recipe (server error)',
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
                                      'Category: ${recipe.category}',
                                      style: TextStyle(
                                        color: Colors.grey.shade700,
                                      ),
                                    ),
                                    // Text(
                                    //   'Date: ${recipe.date.toLocal().toIso8601String().split('T').first}',
                                    //   style: TextStyle(
                                    //     color: Colors.grey.shade700,
                                    //   ),
                                    // ),
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
        onPressed: context.watch<RecipeService>().isOffline
            ? null
            : () => context.push('/add'),
        child: const Icon(Icons.add),
      ),
    );
  }
}
