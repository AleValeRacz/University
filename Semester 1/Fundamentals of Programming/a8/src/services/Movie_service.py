from src.repository.Movie_repository import MovieRepository
from src.domain.movie import Movie
from src.repository.Exceptions import ServiceException, RepositoryException

class MovieService:
    def __init__(self, movie_repository: MovieRepository):
        self._movie_repository = movie_repository

    def add_movie(self, id, title, description, genre):
        """
        Creates a movie based on its id, title, description, genre
        :param id: int
        :param title: str
        :param description: str
        :param genre: str
        :return:
        raises error if encountered
        """
        movie = Movie(id, title, description, genre)
        try:
            self._movie_repository.add_movie(movie)
        except RepositoryException as e:
            raise e

    def remove_movie(self, movie_id):
        """
        removes a cient with a given id
        :param movie_id: int
        :return:
        raises RepositoryError of encountered
        """
        try:
            return self._movie_repository.remove_movie(movie_id)
        except RepositoryException as e:
            raise e

    def update_movie(self, id, title, description, genre):
        """
        updates the title, description, genre of a movie based on its id
        :param id: int
        :param title: str
        :param description: str
        :param genre: str
        :return: -
        """
        self._movie_repository.update_movie(id, title, description, genre)


    def list_movies(self):
        return self._movie_repository.get_movies()

    def search_movies(self, keyword, field):
        return self._movie_repository.search_movies(keyword, field)

    def get_all_movie_ids(self):
        return [movie.get_id for movie in self._movie_repository.get_movies()]
