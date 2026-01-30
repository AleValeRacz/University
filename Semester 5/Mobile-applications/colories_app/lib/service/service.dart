import 'dart:async';
import 'dart:convert';
import 'package:colories_app/model/log.dart';
import 'package:colories_app/repository/app_database.dart';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:web_socket_channel/web_socket_channel.dart';

class LogService extends ChangeNotifier {
  final String baseUrl = "http://10.0.0.164:2621";
  final AppDatabase _repo = AppDatabase.instance;

  List<Log> _logs = [];
  bool _isLoading = false;
  bool _isOperationInProgress = false;
  bool _isOffline = false;

  Map<String, double> _monthlyTotals = {};
  List<MapEntry<String, double>> _topCategories = [];

  Timer? _heartbeatTimer;
  static const Duration _heartbeatInterval = Duration(seconds: 5);

  late final WebSocketChannel _wsChannel;

  final _newLogController = StreamController<Log>.broadcast();
  Stream<Log> get newLogStream => _newLogController.stream;

  // --------------------- Getters ---------------------
  List<Log> get logs => _logs;
  bool get isLoading => _isLoading;
  bool get isOperationInProgress => _isOperationInProgress;
  bool get isOffline => _isOffline;
  Map<String, double> get monthlyTotals => _monthlyTotals;
  List<MapEntry<String, double>> get topCategories => _topCategories;

  // --------------------- Constructor ---------------------
  LogService() {
    _startHeartbeat();
    _initWebSocket();
     loadLogs();
  }

  // --------------------- WebSocket for real-time new logs ---------------------
  void _initWebSocket() {
    try {
      _wsChannel = WebSocketChannel.connect(
        Uri.parse('ws://10.0.0.164:2621/ws/logs'),
      );
      _wsChannel.stream.listen(
        (message) async {
          try {
            final data = json.decode(message);
            final newLog = Log.fromJson(data);

            final alreadyExists = _logs.any((l) => l.id == newLog.id);
            if (alreadyExists) {
              print("WebSocket: Ignoring duplicate log id=${newLog.id}");
              return;
            }

            _logs.insert(0, newLog);
            await _repo.addLog(newLog);
            print("WebSocket: New log received: $newLog");

            notifyListeners();
            _newLogController.sink.add(newLog);
          } catch (e) {
            print("WebSocket parsing error: $e");
          }
        },
        onError: (err) {
          print("WebSocket error: $err");
        },
      );
    } catch (e) {
      print("Failed to connect WebSocket: $e");
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
    try {
      final response = await http
          .get(Uri.parse('$baseUrl/logs'))
          .timeout(const Duration(seconds: 3));

      if (response.statusCode == 200) {
        _setOffline(false);
      } else {
        _setOffline(true);
      }
    } catch (e) {
      _setOffline(true);
      print("Heartbeat error: $e");
    }
  }

  // --------------------- Load logs ---------------------
  Future<void> loadLogs() async {
    _isLoading = true;
    notifyListeners();

    try {
      final response = await http
          .get(Uri.parse('$baseUrl/logs'))
          .timeout(const Duration(seconds: 5));

      if (response.statusCode != 200) throw Exception('Failed to fetch logs');

      final List decoded = json.decode(response.body);
      _logs = decoded.map((e) => Log.fromJson(e)).toList();

      await _repo.replaceAll(_logs);
      print("Loaded ${_logs.length} logs from server");
      _setOffline(false);

    } catch (e) {
      _setOffline(true);
      _logs = await _repo.fetchLogs();
      print("Error loading logs, using local DB: $e");
    }

    _isLoading = false;
    notifyListeners();
  }

  // --------------------- Get log details ---------------------
  Future<Log?> getLogDetails(int id) async {
    try {
      final response = await http
          .get(Uri.parse('$baseUrl/log/$id'))
          .timeout(const Duration(seconds: 5));

      if (response.statusCode != 200)
        throw Exception('Failed to fetch log details');

      final log = Log.fromJson(json.decode(response.body));
      print("Fetched log details from server: $log");
      _setOffline(false);
      return log;
    } catch (e) {
      print("Error fetching log details, using local DB: $e");
      final log = await _repo.fetchLogById(id);
      return log;
    }
  }

  // --------------------- Add log ---------------------
  Future<bool> addLog(Log log) async {
    if (isOffline) {
      print("Cannot add log while offline");
      return false;
    }

    _isOperationInProgress = true;
    notifyListeners();

    try {
      final response = await http.post(
        Uri.parse('$baseUrl/log'),
        headers: {'Content-Type': 'application/json'},
        body: json.encode({
          "date": log.date.toIso8601String(),
          "amount": log.amount,
          "type": log.type,
          "category": log.category,
          "description": log.description,
        }),
      );

      if (response.statusCode != 201) throw Exception('Failed to add log');

      final created = Log.fromJson(json.decode(response.body));
      await _repo.addLog(created);
      _logs.insert(0, created);

      print("Added log: $created");
      notifyListeners();
      return true;
    } catch (e) {
      print("Error adding log: $e");
      _setOffline(true);
      return false;
    } finally {
      _isOperationInProgress = false;
      notifyListeners();
    }
  }

  // --------------------- Delete log ---------------------
  Future<bool> deleteLog(int id) async {
    if (isOffline) {
      print("Cannot delete log while offline");
      return false;
    }

    _isOperationInProgress = true;
    notifyListeners();

    try {
      final response = await http.delete(Uri.parse('$baseUrl/log/$id'));

      if (response.statusCode != 200) throw Exception('Failed to delete log');

      await _repo.deleteLog(id);
      _logs.removeWhere((l) => l.id == id);

      print("Deleted log id=$id");
      notifyListeners();
      return true;
    } catch (e) {
      print("Error deleting log: $e");
      _setOffline(true);
      return false;
    } finally {
      _isOperationInProgress = false;
      notifyListeners();
    }
  }

  // --------------------- Load all logs & compute monthly + top categories ---------------------
  Future<void> loadAllLogsAndCompute() async {
    _isLoading = true;
    notifyListeners();

    List<Log> allLogs = [];
    try {
      final response = await http.get(Uri.parse('$baseUrl/allLogs'));

      if (response.statusCode != 200)
        throw Exception('Failed to fetch allLogs');

      final List decoded = json.decode(response.body);
      allLogs = decoded.map((e) => Log.fromJson(e)).toList();
      await _repo.replaceAll(allLogs);

      print("Fetched ${allLogs.length} logs from server (allLogs)");
      _setOffline(false);
    } catch (e) {
      print("Error fetching allLogs, using local DB: $e");
      _setOffline(true);
      allLogs = await _repo.fetchLogs();
    }

    // ----- Compute monthly totals -----
    final Map<String, double> monthlyMap = {};
    for (final log in allLogs) {
      final key =
          "${log.date.year}-${log.date.month.toString().padLeft(2, '0')}";
      monthlyMap[key] = (monthlyMap[key] ?? 0) + log.amount;
    }
    _monthlyTotals = Map.fromEntries(
      monthlyMap.entries.toList()..sort((a, b) => b.key.compareTo(a.key)),
    );

    // ----- Compute top 3 categories -----
    final Map<String, double> categoryMap = {};
    for (final log in allLogs) {
      categoryMap[log.category] = (categoryMap[log.category] ?? 0) + log.amount;
    }
    _topCategories = categoryMap.entries.toList()
      ..sort((a, b) => b.value.compareTo(a.value));
    if (_topCategories.length > 3)
      _topCategories = _topCategories.sublist(0, 3);

    _isLoading = false;
    notifyListeners();
  }
}
