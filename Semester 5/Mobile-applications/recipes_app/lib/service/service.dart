import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'package:colories_app/model/recipe.dart';
import 'package:colories_app/model/sumCount.dart';
import 'package:colories_app/repository/app_database.dart';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:web_socket_channel/web_socket_channel.dart';

class RecipeService extends ChangeNotifier {
  final String baseUrl = "http://10.0.0.164:2528";
  final AppDatabase _repo = AppDatabase.instance;

  List<Recipe> _recipes = [];
  bool _isLoading = false;
  bool _isOperationInProgress = false;
  bool _isOffline = false;
  bool _isDataLoaded = false;

  Map<String, double> _monthlyAverages = {};
  List<MapEntry<String, double>> _topCategories = [];

  Timer? _heartbeatTimer;
  static const Duration _heartbeatInterval = Duration(seconds: 5);

  late final WebSocketChannel _wsChannel;

  final _newController = StreamController<Recipe>.broadcast();
  Stream<Recipe> get newLogStream => _newController.stream;

  // --------------------- Getters ---------------------
  List<Recipe> get recipes => _recipes;
  bool get isLoading => _isLoading;
  bool get isOperationInProgress => _isOperationInProgress;
  bool get isOffline => _isOffline;
  bool get isdataLoaded => _isDataLoaded;
  Map<String, double> get monthlyAverages => _monthlyAverages;
  List<MapEntry<String, double>> get topCategories => _topCategories;

  // --------------------- Constructor ---------------------
  RecipeService() {
    _startHeartbeat();
    _initWebSocket();
    loadRecipes();
  }

  // --------------------- WebSocket for real-time new logs ---------------------
  void _initWebSocket() {
    try {
      _wsChannel = WebSocketChannel.connect(
        Uri.parse('ws://10.0.0.164:2528/ws/recipes'),
      );
      _wsChannel.stream.listen(
        (message) async {
          try {
            final data = json.decode(message);
            final newRecipe = Recipe.fromJson(data);
            await Future.delayed(const Duration(seconds: 1));
            final alreadyExists =  await _repo.fetchById(newRecipe.id) != null;
            if (alreadyExists) {
              print("WebSocket: Ignoring duplicate recipe id=${newRecipe.id}");
              return;
            }

            final id = await _repo.addItem(newRecipe);
            if(id == 0)
            {
               print("Skipping local list insert for duplicate recipe id=${newRecipe.id}");
               return;
            }
            print("WebSocket: New recipe received: ${newRecipe.id}");

            _recipes.insert(0,newRecipe);
            notifyListeners();
            _newController.sink.add(newRecipe);
          } catch (e) {
            print("WebSocket parsing error: $e");
          }
        },
        onError: (err) {
          print("WebSocket error: $err");

        },
        onDone: () {
        print("WebSocket closed, will retry in 5s");
        Future.delayed(Duration(seconds: 5), _initWebSocket);
      },
      );
    } catch (e) {
      print("Failed to connect WebSocket: $e");
      Future.delayed(Duration(seconds: 5), _initWebSocket);
    }
  }

  // --------------------- Heartbeat for server reachability ---------------------
  void _startHeartbeat() {
    _heartbeatTimer?.cancel();
    _heartbeatTimer = Timer.periodic(
      _heartbeatInterval,
      (_) => _checkServerReachable(),
    );
  }

  void _setOffline(bool value) {
    if (_isOffline != value) {
      _isOffline = value;
      print("Server reachability changed: Offline=$value");
      notifyListeners();
    }
  }

  Future<void> _checkServerReachable() async {
    if (_isLoading) return;
    try {
      final response = await http
          .get(Uri.parse('$baseUrl/recipes'))
          .timeout(const Duration(seconds: 3));
      _setOffline(response.statusCode != 200);
    } on TimeoutException {
      _setOffline(true);
    } on SocketException catch (e) {
      print("Heartbeat socket exception: $e");
      _setOffline(true);
    } catch (e) {
      _setOffline(true);
      print("Heartbeat error: $e");
    }
  }

  // --------------------- Load logs ---------------------
  Future<void> loadRecipes({bool forceServer = false}) async {
    if (_isLoading) return;
    _isLoading = true;
    notifyListeners();

    List<Recipe> newRecipes = [];

    try {
      if (forceServer || !_isDataLoaded) {
        final response = await http
            .get(Uri.parse('$baseUrl/recipes'))
            .timeout(const Duration(seconds: 5));

        if (response.statusCode == 200) {
          final List decoded = json.decode(response.body);
          newRecipes = decoded.map((e) => Recipe.fromJson(e)).toList();

          await _repo.replaceAll(newRecipes);
          print("Loaded ${newRecipes.length} items from server");
           _isDataLoaded = true; 
          
        } else {
          throw Exception("Server returned ${response.statusCode}");
        }
      }////
       else {
      newRecipes = await _repo.fetchAll();
      print("Using local DB, ${newRecipes.length} recipes loaded");
    }
    } on TimeoutException catch (_) {
      print("Timeout while fetching recipes");
      _setOffline(true);
      _recipes = await _repo.fetchAll();
    } catch (e) {
      _setOffline(true);
      _recipes = await _repo.fetchAll();
      print("Error loading items, using local DB: $e");
    }
    _recipes = newRecipes;
    _isLoading = false;
    notifyListeners();
  }



  // --------------------- Get log details ---------------------
  Future<Recipe?> getRecipeDetails(int id) async {
    try {
      final response = await http
          .get(Uri.parse('$baseUrl/log/$id'))
          .timeout(const Duration(seconds: 5));

      if (response.statusCode != 200)
        throw Exception('Failed to fetch log details');

      final recipe = Recipe.fromJson(json.decode(response.body));
      print("Fetched log details from server: $recipe");
      _setOffline(false);
      return recipe;
    } catch (e) {
      print("Error fetching log details, using local DB: $e");
      final recipe = await _repo.fetchById(id);
      return recipe;
    }
  }

  // --------------------- Add log ---------------------
  Future<bool> addRecipe(Recipe recipe) async {
    if (isOffline) {
      print("Cannot add item while offline");
      return false;
    }

    _isOperationInProgress = true;
    notifyListeners();

    try {
      final response = await http.post(
        Uri.parse('$baseUrl/recipe'),
        headers: {'Content-Type': 'application/json'},
        body: json.encode({
          "date": recipe.date.toIso8601String(),
          "title": recipe.title,
          "ingredients": recipe.ingredients,
          "category": recipe.category,
          "rating": recipe.rating,
        }),
      );

      if (response.statusCode != 201) throw Exception('Failed to add recipe');

      final created = Recipe.fromJson(json.decode(response.body));
       final alreadyExists =  await _repo.fetchById(created.id) != null;
      if (alreadyExists) {
              print("AddRecipe: Ignoring duplicate recipe id=${created.id}");
              return true;
            }
      else{
      final id = await _repo.addItem(created);
      if(id != 0 && id != 1) _recipes.insert(0, created);

      print("Added item: with id= ${created.id}");
      notifyListeners();
      return true;
      }
    } catch (e) {
      print("Error adding item: $e");
      _setOffline(true);
      return false;
    } finally {
      _isOperationInProgress = false;
      notifyListeners();
    }
  }

  // --------------------- Delete log ---------------------
  Future<bool> deleteRecipe(int id) async {
    if (isOffline) {
      print("Cannot delete item while offline");
      return false;
    }

    _isOperationInProgress = true;
    notifyListeners();

    try {
      final response = await http.delete(Uri.parse('$baseUrl/recipe/$id'));

      if (response.statusCode != 200)
        throw Exception('Failed to delete recipe');

      await _repo.deleteItem(id);
      _recipes.removeWhere((l) => l.id == id);

      print("Deleted item with id=$id");
      notifyListeners();
      return true;
    } catch (e) {
      print("Error deleting item: $e");
      _setOffline(true);
      return false;
    } finally {
      _isOperationInProgress = false;
      notifyListeners();
    }
  }

  // --------------------- Load all logs & compute monthly + top categories ---------------------
  Future<void> ComputeMonthlyAverages() async {
    _isLoading = true;
    notifyListeners();

    List<Recipe> allRecipes = [];
    try {
      final response = await http.get(Uri.parse('$baseUrl/allRecipes'));

      if (response.statusCode != 200)
        throw Exception('Failed to fetch allRecipes');

      final List decoded = json.decode(response.body);
      allRecipes = decoded.map((e) => Recipe.fromJson(e)).toList();

      print("Fetched ${allRecipes.length} recipes from server (allRecipes)");
      _setOffline(false);
    } catch (e) {
      print("Error fetching allRecipes, using local DB: $e");
      _setOffline(true);
      allRecipes = await _repo.fetchAll();
    }

    // ----- Compute monthly averages -----
    final Map<String,  SumCount> monthlyMap = {};
    for (final recipe in allRecipes) {
      final key =
          "${recipe.date.year}-${recipe.date.month.toString().padLeft(2, '0')}";
      monthlyMap.putIfAbsent(key, () => SumCount()).add(recipe.rating);
    }
    _monthlyAverages = Map.fromEntries(
      monthlyMap.entries.map((e) => MapEntry(e.key, e.value.average)).toList()..sort((a, b) => b.key.compareTo(a.key)),
    );

    // ----- Compute top 3 categories -----
    final Map<String, double> categoryMap = {};
    for (final recipe in allRecipes) {
      categoryMap[recipe.category] = (categoryMap[recipe.category] ?? 0) + recipe.rating;
    }
    _topCategories = categoryMap.entries.toList()
      ..sort((a, b) => b.value.compareTo(a.value));
    if (_topCategories.length > 3)
      _topCategories = _topCategories.sublist(0, 3);

    _isLoading = false;
    notifyListeners();
  }
}
