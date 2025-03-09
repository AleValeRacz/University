
from src.repository.Client_repository import ClientRepository, ClientFileRepo, ClientBinaryRepo
from src.repository.Movie_repository import MovieRepository, MovieFileRepo, MovieBinaryRepo
from src.repository.Rental_repository import RentalRepository, RentalFileRepo, RentalBinaryRepo

from src.repository.Client_repository import ClientRepository, ClientFileRepo
from src.repository.Movie_repository import MovieRepository, MovieFileRepo
from src.repository.Rental_repository import RentalRepository, RentalFileRepo
from src.services.Client_service import ClientService
from src.services.Movie_service import MovieService
from src.services.Rental_service import RentalService
from src.ui.ui import Ui
from services.undo_service import UndoService
from configparser import ConfigParser
def configurate_repo():
    config = ConfigParser()
    config.read("settings.properties")
    repo_type = config["Settings"]["repository"]
    movies_file = config["Settings"]["movies"]
    clients_file = config["Settings"]["clients"]
    rentals_file = config["Settings"]["rentals"]

    if repo_type == "memory":
        client_repo = ClientRepository()
        movie_repo = MovieRepository()
        rental_repo = RentalRepository()
        opt = 1
    elif repo_type == "binary":

        client_repo = ClientBinaryRepo(clients_file)
        movie_repo = MovieBinaryRepo(movies_file)
        rental_repo = RentalBinaryRepo(rentals_file)
        opt = 2

    elif repo_type == "textfile":
        client_repo = ClientFileRepo(clients_file)
        movie_repo = MovieFileRepo(movies_file)
        rental_repo = RentalFileRepo(rentals_file)
        opt = 3
    else:
        raise ValueError("Invalid repository type!")

    return client_repo, movie_repo, rental_repo, opt

def main():
    client_repo, movie_repo, rental_repo, opt = configurate_repo()
    undo_service = UndoService()
    client_service = ClientService(client_repo, undo_service)
    movie_service = MovieService(movie_repo, undo_service)
    rental_service = RentalService(movie_repo, client_repo, rental_repo, undo_service)
    if opt == 2 or opt == 3:
        if client_repo.get_clients() == [] or movie_repo.get_movies() == [] or rental_repo.get_rentals() == []:
            rental_service.initial_data()
            client_repo.save_file()
            movie_repo.save_file()
            rental_repo.save_file()

    else:
        rental_service.initial_data()
    ui = Ui(movie_service, client_service, rental_service, undo_service)
    ui.run()

if __name__ == "__main__":
    main()

