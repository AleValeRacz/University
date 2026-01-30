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
    final path = join(dbPath, "logs.db");

    return openDatabase(
      path,
      version: 1,
      onCreate: _createTables,
    );
  }

  Future<void> _createTables(Database db, int version) async {
    try {
      await db.execute('''
        CREATE TABLE logs(
          id INTEGER PRIMARY KEY,
          date TEXT,
          amount REAL,
          type TEXT,
          category TEXT,
          description TEXT
        );
      ''');
      print('[DB] Tables created successfully.');
    } catch (e) {
      print('[DB][ERROR] Failed to create tables: $e');
    }
  }

  Future<List<Log>> fetchLogs() async {
    try {
      final db = await database;
      final result = await db.query('logs');
      print('[DB] Fetched ${result.length} logs.');
      return result.map((e) => Log.fromMap(e)).toList();
    } catch (e) {
      print('[DB][ERROR] Failed to fetch logs: $e');
      return [];
    }
  }

  Future<void> replaceAll(List<Log> logs) async {
    try {
      final db = await database;
      await db.transaction((txn) async {
        await txn.delete("logs");
        for (final log in logs) {
          await txn.insert(
            "logs",
            log.toJson(),
            conflictAlgorithm: ConflictAlgorithm.replace,
          );
        }
      });
      print('[DB] Replaced all logs with ${logs.length} items.');
    } catch (e) {
      print('[DB][ERROR] Failed to replace logs: $e');
    }
  }

  Future<Log?> fetchLogById(int id) async {
    try {
      final db = await database;
      final result = await db.query(
        'logs',
        where: 'id = ?',
        whereArgs: [id],
        limit: 1,
      );
      if (result.isNotEmpty) {
        print('[DB] Fetched log with id $id.');
        return Log.fromMap(result.first);
      } else {
        print('[DB] No log found with id $id.');
        return null;
      }
    } catch (e) {
      print('[DB][ERROR] Failed to fetch log by id $id: $e');
      return null;
    }
  }

  Future<int> addLog(Log log) async {
    try {
      final db = await database;
      final id = await db.insert(
        'logs',
        log.toJson(),
        conflictAlgorithm: ConflictAlgorithm.replace,
      );
      print('[DB] Inserted log with id $id.');
      return id;
    } catch (e) {
      print('[DB][ERROR] Failed to insert log: $e');
      return -1;
    }
  }

  Future<int> deleteLog(int id) async {
    try {
      final db = await database;
      final count = await db.delete(
        'logs',
        where: 'id = ?',
        whereArgs: [id],
      );
      print('[DB] Deleted $count log(s) with id $id.');
      return count;
    } catch (e) {
      print('[DB][ERROR] Failed to delete log with id $id: $e');
      return 0;
    }
  }
}
