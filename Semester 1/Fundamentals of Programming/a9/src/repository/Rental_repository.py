
import pickle

from src.repository.Exceptions import RepositoryException
from src.domain.rental import Rental
from datetime import datetime

from src.repository.Exceptions import RepositoryException
from src.domain.rental import Rental

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
        return rental

    def find_rental(self, id):
        for rental in self._rentals:
            if rental.get_rental_id == id:
                return rental


    def delete_rental(self, id):
        rental = self.find_rental(id)
        if rental is not None:
            self._rentals.remove(rental)
            return rental



    def get_rentals(self):
        return self._rentals

    def update_rental(self, id, return_d):
        for rent in self._rentals:
            if rent.get_rental_id == id:
                    rent.set_returned_date(return_d)
                    return rent


    def get_rentals_by_client(self, client_id):
        elements = []
        for rental in self._rentals:
            if rental.get_client_id == client_id:
                elements.append(rental)
        return elements


    def save_rentals(self, rentals):
        self._rentals = rentals

class RentalFileRepo(RentalRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name

    def __load_file(self):
        try:
            with open(self._file_name, "r") as f:
                lines = f.readlines()
                for line in lines:
                    data = line.split(",")
                    data = [elem.strip() for elem in data]
                    rental_id = int(data[0])
                    movie_id = int(data[1])
                    client_id = int(data[2])
                    #date_object = datetime.strptime(date_str, "%Y-%m-%d")
                    rented_d = datetime.strptime(data[3],"%Y-%m-%d" )
                    due_d = datetime.strptime(data[4],"%Y-%m-%d" )
                    if data[5] == "None":
                        return_d = None
                    else:
                        return_d = datetime.strptime(data[5],"%Y-%m-%d" )
                    rental = Rental(rental_id,movie_id,client_id, rented_d, due_d, return_d)
                    super().add_rental(rental)
        except ValueError:
            pass


    def __load_file(self):
        with open(self._file_name, "r") as f:
            lines = f.readlines()
            for line in lines:
                data = line.split(",")
                data = [elem.strip() for elem in data]
                rental = Rental(data[0],[data[1]],data[2], data[3], data[4],data[5])
                super().add_rental(rental)


    def save_file(self):
        with open(self._file_name, "w") as f:
            for rental in super().get_rentals():
                rented_date_str = rental.get_rented_date.strftime("%Y-%m-%d")
                due_date_str = rental.get_due_date.strftime("%Y-%m-%d")
                returned_date_str = (rental.get_returned_date.strftime("%Y-%m-%d")if rental.get_returned_date is not None else "None")
                f.write(f"{rental.get_rental_id},{rental.get_movie_id},{rental.get_client_id}, {rented_date_str},{due_date_str},{returned_date_str}\n")



    def add_rental(self, rental):
        super().add_rental(rental)
        self.save_file()

    def delete_rental(self, id):
        super().delete_rental(id)
        self.save_file()

    def update_rental(self, id, return_d):
        super().update_rental(id, return_d)
        self.save_file()

class RentalBinaryRepo(RentalRepository):
        def __init__(self, file_name):
            super().__init__()
            self._file_name = file_name
            self.__load()

        def __load(self):
            try:
                with open(self._file_name, "rb") as f:
                    rentals = pickle.load(f)
                    super().save_rentals(rentals)
            except (EOFError, FileNotFoundError):
                    pass

        def save_file(self):
            try:
                rentals = open(self._file_name, "wb")
                pickle.dump(super().get_rentals(), rentals)
                rentals.close()
            except IOError:
                raise RepositoryException("File error!")


        def add_rental(self, rental):
            super().add_rental(rental)
            self.save_file()

        def delete_rental(self, id):
            super().delete_rental(id)
            self.save_file()

        def update_rental(self, id, return_d):
            super().update_rental(id, return_d)
            self.save_file()



