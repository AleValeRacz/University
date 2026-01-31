import 'package:colories_app/model/log.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:colories_app/service/service.dart';

class ViewRecipeScreen extends StatelessWidget {
  final int recipeId;

  const ViewRecipeScreen({super.key, required this.recipeId});

  @override
  Widget build(BuildContext context) {
    return FutureBuilder<Recipe?>(
      future: context.read<RecipeService>().getRecipeDetails(recipeId),
      builder: (context, snapshot) {
        if (snapshot.connectionState == ConnectionState.waiting) {
          return const Scaffold(
            body: Center(child: CircularProgressIndicator()),
          );
        }

        if (!snapshot.hasData) {
          return const Scaffold(
            body: Center(child: Text('Recipe not found')),
          );
        }

        final log = snapshot.data!;
        return Scaffold(
          appBar: AppBar(title: const Text('Recipe Details')),
          body: Padding(
            padding: const EdgeInsets.all(16),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text('Title: ${log.title}'),
                Text('Date: ${log.date.toLocal()}'),
                Text('Category: ${log.category}'),
                Text('Ingredients: ${log.ingredients}'),
                Text('rating: ${log.rating}'),
              ],
            ),
          ),
        );
      },
    );
  }
}
