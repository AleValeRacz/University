import 'package:colories_app/model/log.dart';
import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';

class AppDatabase {
  static Database? _db;
  AppDatabase._();
  static final AppDatabase instance = AppDatabase._();

  Future<Database> get database async {
    if (_db != null) return _db!;
    _db = await _init();
    return _db!;
  }

  Future<Database> _init() async {
    final dbPath = await getDatabasesPath();
    final path = join(dbPath, "recipes.db");

    return openDatabase(
      path,
      version: 1,
      onCreate: _createTables,
    );
  }

  Future<void> _createTables(Database db, int version) async {
    try {
      await db.execute('''
        CREATE TABLE recipes(
          id INTEGER PRIMARY KEY,
          date TEXT,
          title TEXT,
          ingredients TEXT,
          category TEXT,
          rating REAL
        );
      ''');
      print('[DB] Tables created successfully.');
    } catch (e) {
      print('[DB][ERROR] Failed to create tables: $e');
    }
  }

  Future<List<Recipe>> fetchAll() async {
    try {
      final db = await database;
      final result = await db.query('recipes');
      print('[DB] Fetched ${result.length} recipes.');
      return result.map((e) => Recipe.fromMap(e)).toList();
    } catch (e) {
      print('[DB][ERROR] Failed to fetch recipes: $e');
      return [];
    }
  }

  Future<void> replaceAll(List<Recipe> items) async {
    try {
      final db = await database;
      await db.transaction((txn) async {
        await txn.delete("recipes");
        for (final item in items) {
          await txn.insert(
            "recipes",
            item.toJson(),
            conflictAlgorithm: ConflictAlgorithm.replace,
          );
        }
      });
      print('[DB] Replaced all recipes with ${items.length} items.');
    } catch (e) {
      print('[DB][ERROR] Failed to replace recipes: $e');
    }
  }

  Future<Recipe?> fetchById(int id) async {
    try {
      final db = await database;
      final result = await db.query(
        'recipes',
        where: 'id = ?',
        whereArgs: [id],
        limit: 1,
      );
      if (result.isNotEmpty) {
        print('[DB] Fetched item with id $id.');
        return Recipe.fromMap(result.first);
      } else {
        print('[DB] No item found with id $id.');
        return null;
      }
    } catch (e) {
      print('[DB][ERROR] Failed to fetch item by id $id: $e');
      return null;
    }
  }

  Future<int> addItem(Recipe log) async {
    try {
      final db = await database;
      final id = await db.insert(
        'recipes',
        log.toJson(),
        conflictAlgorithm: ConflictAlgorithm.ignore,
      );
      if (id == 0) {
      print('[DB] Recipe id=${log.id} already exists, not inserted.');
      return 0; 
    } else {
      print('[DB] Inserted recipe with id $id.');
      return id;
    }
    } catch (e) {
      print('[DB][ERROR] Failed to insert recipe: $e');
      return -1;
    }
  }

  Future<int> deleteItem(int id) async {
    try {
      final db = await database;
      final count = await db.delete(
        'recipes',
        where: 'id = ?',
        whereArgs: [id],
      );
      print('[DB] Deleted $count items(s) with id $id.');
      return count;
    } catch (e) {
      print('[DB][ERROR] Failed to delete recipe with id $id: $e');
      return 0;
    }
  }
}
