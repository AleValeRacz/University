import unittest
from src.domain.movie import Movie
from src.domain.client import Client
from src.repository.Client_repository import ClientRepository
from src.repository.Movie_repository import MovieRepository

class TestMovie(unittest.TestCase):
    def setUp(self):
        self._repo = MovieRepository()

    def test_add_movie(self):
        movie = Movie(id=421, title="The Great Movie", description="A fantastic movie", genre="Action")
        self._repo.add_movie(movie)
        movies = self._repo.get_movies()
        self.assertIn(movie, movies)

    def test_get_all_movies(self):
        self.assertEqual(self._repo.get_movies(), [])
        movies = [
            Movie(id=1, title="Movie 1", description="Description 1", genre="Action"),
            Movie(id=2, title="Movie 2", description="Description 2", genre="Drama"),
            Movie(id=3, title="Movie 3", description="Description 3", genre="Comedy")
        ]
        for movie in movies:
            self._repo.add_movie(movie)
        self.assertEqual(self._repo.get_movies(), movies)

    def test_update(self):
        movie = Movie(id=1, title="The Great Movie", description="A fantastic movie", genre="Action")
        self._repo.add_movie(movie)
        new_title = "Updated Title"
        new_description = "Updated Description"
        new_genre = "Updated genre"
        self._repo.update_movie(movie.get_id, new_title, new_description, new_genre)
        self.assertEqual(movie.get_title, new_title)
        self.assertEqual(movie.get_description, new_description)
        self.assertEqual(movie.get_genre, new_genre)

    def test_remove(self):
        movie = Movie(id=1, title="The Great Movie", description="A fantastic movie", genre="Action")
        self._repo.add_movie(movie)
        self._repo.remove_movie(movie.get_id)
        self.assertNotIn(movie, self._repo.get_movies())


class TestClientRepo(unittest.TestCase):
    def setUp(self):
        self._repo = ClientRepository()

    def test_add_client(self):
        # Test adding a new client
        client = Client(client_id=1, name="John Doe")
        self._repo.add_client(client)
        clients = self._repo.get_clients()
        self.assertIn(client, clients)

    def test_get_all_clients(self):
        self.assertEqual(self._repo.get_clients(), [])
        clients = [
            Client(client_id=1, name="Mihai"),
            Client(client_id=2, name="Andra"),
            Client(client_id=3, name="Bob")
        ]
        for client in clients:
            self._repo.add_client(client)
        self.assertEqual(self._repo.get_clients(), clients)

    def test_update(self):
        client = Client(client_id=1, name="Mihai")
        self._repo.add_client(client)
        new_name = "Mihai Updated"
        self._repo.update_client(client.get_id, new_name)
        self.assertEqual(client.get_name, new_name)

    def test_remove(self):
        client = Client(client_id=1, name="Mara")
        self._repo.add_client(client)
        self._repo.remove_client(client.get_id)
        self.assertNotIn(client, self._repo.get_clients())

if __name__ == '__main__':
    unittest.main()






