
class Rental:
    def __init__(self, rental_id, movie_id, client_id, rented_date, due_date, returned_date):
        self.__rental_id = rental_id
        self.__movie_id = movie_id
        self.__client_id = client_id
        self.__rented_date = rented_date
        self.__due_date = due_date
        self.__returned_date = returned_date

    @property
    def get_rental_id(self):
        return self.__rental_id

    @property
    def get_movie_id(self):
        return self.__movie_id

    @property
    def get_client_id(self):
        return self.__client_id

    @property
    def get_rented_date(self):
        return self.__rented_date

    @property
    def get_due_date(self):
        return self.__due_date

    @property
    def get_returned_date(self):
        return self.__returned_date

    def set_returned_date(self, returned_date):
        self.__returned_date = returned_date

    def __str__(self):
        return f" ID:{self.__rental_id}; Movie ID:{self.__movie_id}; Client ID:{self.__client_id}; Rented date:{self.__rented_date}; Due_date:{self.__due_date}; Returned_date:{self.__returned_date}"

    def __len__(self):
        return (self.__returned_date - self.__rented_date).days + 1

