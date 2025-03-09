from src.repository.Exceptions import RepositoryException
class MovieRepository:
    def __init__(self):
        self._movies = []

    def check_if_present(self, id):
        """
        Checks if a movie with a given id is present in the repo
        :param id: int
        :return: -
        raises Repository exception if the movie is already in the repo
        """
        ids = []
        for movie in self._movies:
            ids.append(movie.get_id)
        if id in ids:
            raise RepositoryException("This movie is already in the repository")

    def check_if_not_present(self, id):
        """
        Checks if a movie is not present in the repo
        :param id: int
        :return: -
        raises RepositoryException if the movie is not in the repo
        """
        ids = []
        for movie in self._movies:
            ids.append(movie.get_id)
        if id not in ids:
            raise RepositoryException("This movie is not in the repository")

    def add_movie(self, movie):
        """
        add a movie to the repo
        :param movie: obj in class Movie
        :return: -
        """
        self.check_if_present(movie.get_id)
        self._movies.append(movie)

    def remove_movie(self, movie_id: int):
        """
        removes a movie with a given id
        :param movie_id:int
        :return: -
        """
        self.check_if_not_present(movie_id)
        self._movies = [m for m in self._movies if m.get_id != movie_id]

    def update_movie(self, movie_id, new_title, new_description, new_genre):
        """
        Updates the title, description and genre of a movie based on its id
        :param movie_id: int
        :param new_title: str
        :param new_description: str
        :param new_genre: str
        :return: -
        """
        for movie in self._movies:
            if movie.get_id == movie_id:
                movie.set_title(new_title)
                movie.set_description(new_description)
                movie.set_genre(new_genre)

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
