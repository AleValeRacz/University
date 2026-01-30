class Log{
  int id;
  DateTime date;
  double amount;
  String type;
  String category;
  String description;



Log({required this.id, required this.date, required this.amount, required this.type, required this.category,  required this.description});


  factory Log.fromMap(Map<String, dynamic> map) {
    return Log(
      id: map['id'] as int,
      date: DateTime.parse(map['date'] as String),
      amount: (map['amount'] as num).toDouble(),
      type: map['type'] as String,
      category: map['category'] as String,
      description: map['description'] as String,
    );
  }


  factory Log.fromJson(Map<String, dynamic> json) => Log(
        id: json['id'] as int,
      date: DateTime.parse(json['date']),
      amount: (json['amount'] as num).toDouble(),
      type: json['type'],
      category: json['category'],
      description: json['description'],
      );

  Map<String, dynamic> toJson() => {
        "id": id,
        "date": date.toIso8601String(),
        "amount": amount,
        "type": type,
        "category": category,
        "description": description
      };

}