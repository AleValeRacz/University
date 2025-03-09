import random
class Movie:
    def __init__(self, id, title, description, genre):
        self.__id = id
        self.__title = title
        self.__description = description
        self.__genre = genre

    @property
    def get_id(self):
        return self.__id

    @property
    def get_title(self):
        return self.__title

    @property
    def get_description(self):
        return self.__description

    @property
    def get_genre(self):
        return self.__genre

    def set_title(self,name):
        self.__title = name

    def set_description(self,desc):
        self.__description = desc

    def set_genre(self, genre):
        self.__genre = genre


    def __str__(self):
        return "ID: " + str(self.__id) + "; Title: "+ str (self.__title) + "; Description: " + str(self.__description) + "; Genre: " + str(self.__genre)

def generate_movies(n):
        movies = []
        id = 400
        title_list = ["Inception", "The Shawshank Redemption", "The Godfather", "Pulp Fiction", "The Dark Knight", "Fight Club", "Forrest Gump", "The Matrix", "The Silence of the Lambs", "The Green Mile", "Schindler's List", "The Lord of the Rings", "Star Wars", "Casablanca", "Gone with the Wind", "Titanic", "The Avengers", "Jurassic Park", "Avatar", "The Lion King"]
        genre_list = ["Action", "Drama", "Crime", "Sci-Fi", "Adventure", "Fantasy", "Romance", "Thriller", "Horror", "Comedy", "Animation", "Mystery", "Western", "Family", "War", "History", "Biography", "Musical", "Sport", "Music"]
        description_list = ["nice", "fantastic", "bad", "sad", "dramatic", "funny", "gritty", "fascinating", "inspiring", "boring", "long"]
        for i in range(n):
            title = random.choice(title_list)
            description = random.choice(description_list)
            genre = random.choice(genre_list)
            movies.append(Movie(id,title,description, genre))
            id += 1
        return movies

