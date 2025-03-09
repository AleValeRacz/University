from src.repository.Movie_repository import MovieRepository
from src.domain.movie import Movie
from src.repository.Exceptions import ServiceException, RepositoryException
from src.services.undo_service import FunctionCall, Operation
class MovieService:
    def __init__(self, movie_repository: MovieRepository, undo_service):
        self._movie_repository = movie_repository
        self._undo = undo_service

    def add_movie(self, id, title, description, genre):
        movie = Movie(id, title, description, genre)
        try:
            self._movie_repository.add_movie(movie)
            redo = FunctionCall(self._movie_repository.add_movie, movie)
            undo = FunctionCall(self._movie_repository.remove_movie, id)
            self._undo.record(Operation(undo,redo))
            return movie
        except RepositoryException as e:
            raise e

    def remove_movie(self, movie_id):
        try:
            movie = self._movie_repository.remove_movie(movie_id)
            redo = FunctionCall(self._movie_repository.remove_movie, movie_id)
            undo = FunctionCall(self._movie_repository.add_movie, movie)
            self._undo.record(Operation(undo,redo))
            return movie
        except RepositoryException as e:
            raise e

    def update_movie(self, id, title, description, genre):
            movie = self._movie_repository.find_movie(id)
            if movie is None:
                raise RepositoryException("There's no movie with this id!")
            undo = FunctionCall(self._movie_repository.update_movie, id, movie.get_title, movie.get_description, movie.get_genre)
            movie = self._movie_repository.update_movie(id, title, description, genre)
            redo = FunctionCall(self._movie_repository.update_movie, id, title, description, genre)
            self._undo.record(Operation(undo,redo))
            return movie


    def list_movies(self):
        return self._movie_repository.get_movies()

    def search_movies(self, keyword, field):
        return self._movie_repository.search_movies(keyword, field)

    def get_all_movie_ids(self):
        return [movie.get_id for movie in self._movie_repository.get_movies()]
