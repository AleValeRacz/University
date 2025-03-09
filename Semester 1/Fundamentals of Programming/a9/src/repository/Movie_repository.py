from src.repository.Exceptions import RepositoryException
from src.domain.movie import Movie

import pickle


class MovieRepository:
    def __init__(self):
        self._movies = []

    def check_if_present(self, id):
        ids = []
        for movie in self._movies:
            ids.append(movie.get_id)
        if id in ids:
            raise RepositoryException("This movie is already in the repository")

    def check_if_not_present(self, id):
        ids = []
        for movie in self._movies:
            ids.append(movie.get_id)
        if id not in ids:
            raise RepositoryException("This movie is not in the repository")

    def add_movie(self, movie):
        self.check_if_present(movie.get_id)
        self._movies.append(movie)
        return movie

    def remove_movie(self, movie_id: int):
        self.check_if_not_present(movie_id)
        movie = self.find_movie(movie_id)
        self._movies.remove(movie)
        return movie

    def update_movie(self, movie_id, new_title, new_description, new_genre):
        for movie in self._movies:
            if movie.get_id == movie_id:
                movie.set_title(new_title)
                movie.set_description(new_description)
                movie.set_genre(new_genre)
                return movie

    def find_movie(self, id):
        for movie in self._movies:
            if movie.get_id == id:
                return movie

    def get_movies(self):
        return self._movies

    def get_movie_by_id(self, id):
        for movie in self._movies:
            if movie.get_id == id:
                return movie

    def search_movies(self, keyword, field):
        keyword = keyword.lower()
        fields = ['id', 'title', 'description', 'genre']
        if field not in fields:
            raise RepositoryException("Invalid search field")
        return [movie for movie in self._movies if keyword in str(getattr(movie, f'get_{field}')).lower()]

    def save_movies(self, movies):
        self._movies = movies


class MovieFileRepo(MovieRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name

        self.__load_file()

    def __load_file(self):
        try:
            with open(self._file_name, "r") as f:
                lines = f.readlines()
                for line in lines:
                    data = line.split(",")
                    data = [elem.strip() for elem in data]
                    id = int(data[0])
                    name = str(data[1])
                    desc = str(data[2])
                    genre = str(data[3])
                    movie = Movie(id, name, desc, genre)
                    super().add_movie(movie)
        except ValueError:
            pass

        self.save_file()
        self.__load_file()

    def __load_file(self):
        with open(self._file_name, "r") as f:
            lines = f.readlines()
            for line in lines:
                data = line.split(",")
                data = [elem.strip() for elem in data]
                movie = Movie(data[0], [data[1]], data[2], data[3])
                super().add_movie(movie)

    def save_file(self):
        with open(self._file_name, "w") as f:
            for movie in super().get_movies():
                f.write(f"{movie.get_id},{movie.get_title},{movie.get_description},{movie.get_genre}\n")

    def add_movie(self, movie):
        super().add_movie(movie)
        self.save_file()

    def remove_movie(self, movie_id: int):
        super().remove_movie(movie_id)
        self.save_file()

    def update_movie(self, movie_id, new_title, new_description, new_genre):
        super().update_movie(movie_id, new_title, new_description, new_genre)
        self.save_file()


class MovieBinaryRepo(MovieRepository):
    def __init__(self, movies_file):
        super().__init__()
        self._movies_file = movies_file
        self.__load()

    def __load(self):
        try:
            with open(self._movies_file, "rb") as f:
                movies = pickle.load(f)
                super().save_movies(movies)
        except (EOFError, FileNotFoundError):
            pass

    def save_file(self):
        try:
            with open(self._movies_file, "wb") as f:
                pickle.dump(super().get_movies(), f)
        except IOError:
            raise RepositoryException("File error!")

    def add_movie(self, movie):
        super().add_movie(movie)
        self.save_file()

    def remove_movie(self, movie_id: int):
        super().remove_movie(movie_id)
        self.save_file()

    def update_movie(self, movie_id, new_title, new_description, new_genre):
        super().update_movie(movie_id, new_title, new_description, new_genre)
        self.save_file()
