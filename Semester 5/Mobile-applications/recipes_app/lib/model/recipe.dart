class Recipe{
  int id;
  DateTime date;
  String title;
  String ingredients;
  String category;
  double rating;



Recipe({required this.id, required this.date, required this.title, required this.ingredients, required this.category,  required this.rating});


  factory Recipe.fromMap(Map<String, dynamic> map) {
    return Recipe(
      id: map['id'] as int,
      date: DateTime.parse(map['date'] as String),
      title: map['title'] as String,
      ingredients: map['ingredients'] as String,
      category: map['category'] as String,
      rating: (map['rating'] as num).toDouble(),
    );
  }


  factory Recipe.fromJson(Map<String, dynamic> json) => Recipe(
        id: json['id'] as int,
      date: DateTime.parse(json['date']),
      title:json['title'],
      ingredients: json['ingredients'],
      category: json['category'],
      rating: (json['rating'] as num).toDouble(),
      );

  Map<String, dynamic> toJson() => {
        "id": id,
        "date": date.toIso8601String(),
        "title": title,
        "ingredients": ingredients,
        "category": category,
        "rating": rating,
      };

}