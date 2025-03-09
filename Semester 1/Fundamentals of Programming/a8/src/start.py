from src.repository.Client_repository import ClientRepository
from src.repository.Movie_repository import MovieRepository
from src.repository.Rental_repository import RentalRepository
from src.services.Client_service import ClientService
from src.services.Movie_service import MovieService
from src.services.Rental_service import RentalService
from src.ui.ui import Ui
def main():
    client_repo = ClientRepository()
    movie_repo = MovieRepository()
    rental_repo = RentalRepository()
    client_service = ClientService(client_repo)
    movie_service = MovieService(movie_repo)
    rental_service = RentalService(movie_repo, client_repo, rental_repo)
    ui = Ui(movie_service, client_service, rental_service)

    ui.run()

if __name__ == "__main__":
    main()

