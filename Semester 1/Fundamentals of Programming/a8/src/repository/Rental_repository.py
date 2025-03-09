from src.repository.Exceptions import RepositoryException
class RentalRepository:
    def __init__(self):
        self._rentals = []

    def check_if_present(self, id):
        ids = []
        for rental in self._rentals:
            ids.append(rental.get_rental_id)
        if id in ids:
            raise RepositoryException("This rental is already in the repository")

    def add_rental(self, rental):
        self.check_if_present(rental.get_rental_id)
        self._rentals.append(rental)

    def get_rentals(self):
        return self._rentals

    def update_rental(self, id, return_d):
        for rent in self._rentals:
            if rent.get_rental_id == id:
                if rent.get_returned_date is None:
                    rent.set_returned_date(return_d)
                else:
                    raise RepositoryException("Already returned!")

    def get_rentals_by_client(self, client_id):
        elements = []
        for rental in self._rentals:
            if rental.get_client_id == client_id:
                elements.append(rental)
        return elements











