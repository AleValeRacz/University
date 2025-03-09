from src.domain.rental import Rental
from src.repository.Exceptions import RepositoryException, ServiceException, EntityNotFoundError
from src.repository.Rental_repository import RentalRepository
import random
from datetime import date, timedelta
from src.domain.movie import generate_movies
from src.domain.client import generate_clients
from src.services.undo_service import Operation, FunctionCall, UndoService
class RentalService:
    def __init__(self, movie_repo, client_repo, rental_repo: RentalRepository, undo_service: UndoService):
        self._movie_repo = movie_repo
        self._client_repo = client_repo
        self._repo = rental_repo
        self._undo = undo_service

        #self.initial_data()


    def generate_rentals(self,n):
        clients = generate_clients(n)
        movies = generate_movies(n)
        id = 500
        rentals = []
        i = 0
        while i < n:
            client = random.choice(clients)
            movie = random.choice(movies)
            try:
                self.check_late_returns(client.get_id)
            except ServiceException:
                continue
            rented_date = date.today() + timedelta(days=random.randint(-80, -10))
            due_date = rented_date + timedelta(days=random.randint(1, 20))
            returned_date = rented_date + timedelta(days=random.randint(1, 20))
            if returned_date > date.today():
                returned_date = None
            rentals.append(Rental(id,movie.get_id, client.get_id,rented_date, due_date, returned_date))
            id+= 1
            i += 1
        return movies, clients, rentals

    def initial_data(self):
        movies, clients, rentals = self.generate_rentals(20)
        for movie in movies:
            self._movie_repo.add_movie(movie)
        for client in clients:
            self._client_repo.add_client(client)
        for rental in rentals:
            self._repo.add_rental(rental)

    def validate_movie(self, movie_id):
        found = False
        for el in self._movie_repo.get_movies():
            if el.get_id == movie_id:
                found = True
        if found is False:
            raise EntityNotFoundError("Movie", movie_id)

    def validate_client(self, client_id):
        found = False
        for client in self._client_repo.get_clients():
            if client.get_id == client_id:
                found = True
        if found is False:
            raise EntityNotFoundError("Client", client_id)

    def check_late_returns(self, client_id):
        for rental in self._repo.get_rentals_by_client(client_id):
            if rental.get_returned_date is not None and rental.get_returned_date > rental.get_due_date:
                raise ServiceException("Client is not eligible for renting.")

    def rent_movie(self, rental_id, movie_id, client_id, rented_date, due_date):
        self.validate_movie(movie_id)
        self.validate_client(client_id)
        self.check_late_returns(client_id)
        self._repo.add_rental(Rental(rental_id, movie_id, client_id, rented_date, due_date, None))
        rental = self._repo.find_rental(rental_id)
        redo = FunctionCall(self._repo.add_rental,rental)
        undo = FunctionCall(self._repo.delete_rental, rental_id)
        self._undo.record(Operation(undo,redo))
        return rental

    def return_movie(self, rental_id, returned_date):
            rental = self._repo.find_rental(rental_id)

            if rental is None:
                raise EntityNotFoundError("Rental", rental_id)

            if rental.get_returned_date is not None:
                raise RepositoryException("Already returned!")
            undo = FunctionCall(self._repo.update_rental, rental_id, None)
            self._repo.update_rental(rental_id, returned_date)
            redo = FunctionCall(self._repo.update_rental, rental_id, returned_date)
            self._undo.record(Operation(undo,redo))
            return rental



    def list_rentals(self):
        return self._repo.get_rentals()


    def most_rented_movies(self):
        all_movies = []
        for movie in self._movie_repo.get_movies():
            all_movies.append(movie)
        all_rentals = []
        for rental in self._repo.get_rentals():
            all_rentals.append(rental)

        movie_rental_days = {}
        for movie in all_movies:
            movie_rental_days[movie.get_id] = 0
            for rental in all_rentals:
                if movie.get_id == rental.get_movie_id and rental.get_returned_date is not None:
                    movie_rental_days[movie.get_id] += len(rental)
        result = []
        for movie_id in movie_rental_days:
            item = (movie_id,movie_rental_days[movie_id])
            result.append(item)
        result.sort(key = lambda x: x[1], reverse=True)
        return result

    def most_active_clients(self):
        all_clients = self._client_repo.get_clients()
        all_rentals = self._repo.get_rentals()
        client_rental_days = {}
        for client in all_clients:
            client_rental_days[client.get_id] = 0
            for rental in all_rentals:
                if client.get_id == rental.get_client_id and rental.get_returned_date is not None:
                    client_rental_days[client.get_id] += len(rental)
        result = []
        for client_id in client_rental_days:
            item = (client_id, client_rental_days[client_id])
            result.append(item)
        result.sort(key =lambda x: x[1], reverse=True)
        return result

    def late_rentals(self):
        late_rentals = []
        all_rentals = self._repo.get_rentals()
        for rental in all_rentals:
            due_date = rental.get_due_date
            returned_date = rental.get_returned_date
            if returned_date is not None and due_date < returned_date:
                days_of_delay = (returned_date - due_date).days
                late_rentals.append((rental.get_rental_id, days_of_delay))
            late_rentals.sort(key = lambda x: x[1], reverse = True)
        return late_rentals













