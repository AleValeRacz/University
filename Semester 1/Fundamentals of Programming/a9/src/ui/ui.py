from src.services.Movie_service import MovieService
from src.services.Client_service import ClientService
from src.services.Rental_service import RentalService
from src.repository.Exceptions import RepositoryException, ServiceException, EntityNotFoundError
from datetime import datetime, date
from src.services.undo_service import UndoService, UndoError


class Ui:
    def __init__(self, movie_service: MovieService, client_service: ClientService, rental_service: RentalService,
                 undo_service: UndoService):
        self._movie_service = movie_service
        self._client_service = client_service
        self._rental_service = rental_service
        self._undo_service = undo_service

    def print_general_menu(self):
        print("""
         Menu
        1.Manage movies.
        2.Manage clients.
        3.Rent a movie.
        4.Search for movie.
        5.Search for client.
        6.Create statistics. 
        7.Undo.
        8.Redo.
        9.Exit.
        """)

    def print_menu_movies(self):
        print("""
        1.Add a movie.
        2.Remove a movie.
        3.Update information about a movie.
        4.List all movies.
        5.Return to main menu.
        """)

    def print_menu_client(self):
        print("""
        1.Add a client.
        2.Remove a client.
        3.Update information about a client.
        4.List all clients.
        5.Return to main menu.
        """)

    def print_menu_rentals(self):
        print("""
        1.Rent a movie.
        2.Return a movie.
        3.Print rentals.
        4.Return to main menu.
        """)

    def print_menu_statistics(self):
        print("""
        1.Most rented movies.
        2.Most active clients.
        3.Late rentals.
        """)

    def run(self):
        while True:
            self.print_general_menu()
            choice = input("Enter your choice: ")

            if choice == '1':
                self.print_menu_movies()
                option = input("Enter your choice: ")

                if option == '1':
                    try:
                        id = int(input("Enter movie id:"))
                        title = input("Enter movie title: ")
                        description = input("Enter movie description: ")
                        genre = input("Enter movie genre: ")
                        movie = self._movie_service.add_movie(id, title, description, genre)
                    except (RepositoryException, ValueError) as e:
                        print(e)

                elif option == '2':
                    try:
                        movie_id = int(input("Enter movie ID to remove: "))
                        removed_movie = self._movie_service.remove_movie(movie_id)
                        print("removed successfully")
                    except (RepositoryException, ValueError) as e:
                        print(e)

                elif option == '3':
                    try:
                        id = int(input("Enter the the id of the movie to be updated: "))
                        updated_title = input("Enter new movie title: ")
                        updated_description = input("Enter new movie description: ")
                        updated_genre = input("Enter new movie genre: ")
                        movie = self._movie_service.update_movie(id, updated_title, updated_description, updated_genre)
                    except (ValueError, RepositoryException) as e:
                        print(e)

                elif option == '4':
                    print("List all movies:")
                    movies = self._movie_service.list_movies()
                    for movie in movies:
                        print(movie)

                elif option == '5':
                    pass
                else:
                    print("Invalid choice!")


            elif choice == '2':
                self.print_menu_client()
                option = input("Enter your choice: ")

                if option == '1':
                    try:
                        id = int(input("Enter client id:"))
                        name = input("Enter client name:")
                        client = self._client_service.add_client(id, name)
                    except (ValueError, RepositoryException) as e:
                        print(e)

                elif option == '2':
                    try:
                        id = int(input("Enter client ID to remove: "))
                        removed_client = self._client_service.remove_client(id)
                        print("Removed successfully")
                    except (RepositoryException, ValueError) as e:
                        print(e)

                elif option == '3':
                    try:
                        id = int(input("Enter the the id of the client to be updated: "))
                        updated_name = input("Enter new client name: ")
                        client = self._client_service.update_client(id, updated_name)
                    except (ValueError, RepositoryException) as e:
                        print(e)

                elif option == '4':
                    print("List all clients:")
                    clients = self._client_service.list_clients()
                    for client in clients:
                        print(client)

                elif option == '5':
                    pass
                else:
                    print("Invalid choice!")

            elif choice == '3':
                self.print_menu_rentals()
                option = input(" Chose your option:")
                if option == '1':
                    try:
                        id = int(input("Enter the id for the rental:"))
                        movie = int(input("Enter the id of an existing movie: "))
                        client = int(input("Enter the id of an existing client: "))
                        start = input("enter the date it was rented: ")
                        datetime.strptime(start, '%Y-%m-%d')
                        end = input("Enter the due date: ")
                        datetime.strptime(end, '%Y-%m-%d')
                        rental = self._rental_service.rent_movie(id, movie, client, start, end)
                    except (EntityNotFoundError, ServiceException, RepositoryException, ValueError) as e:
                        print(e)
                elif option == '3':
                    rentals = self._rental_service.list_rentals()
                    for rental in rentals:
                        print(rental)

                elif option == '2':
                    try:
                        id = int(input("Enter the id of a rental to return: "))
                        returned_date = date.today()

                        rental = self._rental_service.return_movie(id, returned_date)

                    except (RepositoryException, ValueError, EntityNotFoundError) as e:
                        print(e)
                elif option == '4':
                    pass
                else:
                    print("Invalid choice!")

            elif choice == '4':
                field = input("Chose the field by witch to search (id, title, description, genre): ")
                keyword = input("word to search for: ")
                try:
                    results = self._movie_service.search_movies(keyword, field)
                    if results:
                        for result in results:
                            print(result)
                    else:
                        print("no matches found")
                except RepositoryException as e:
                    print(e)
            elif choice == '5':
                field = input("Chose the field by witch to search(id or name): ")
                keyword = input("Word to search: ")
                try:
                    results = self._client_service.search_clients(keyword, field)
                    if results:
                        for result in results:
                            print(result)
                    else:
                        print("No matches found")
                except RepositoryException as e:
                    print(e)
            elif choice == '6':
                self.print_menu_statistics()
                option = input("enter choice: ")
                if option == '1':
                    most_rented = self._rental_service.most_rented_movies()
                    for id, rental_days in most_rented:
                        print(f"Movie id: {id}, Rental Days: {rental_days}")
                elif option == '2':
                    most_active = self._rental_service.most_active_clients()
                    for client, rental_days in most_active:
                        print(f"Client id: {client}, Rental Days: {rental_days}")
                elif option == '3':
                    late_rental = self._rental_service.late_rentals()
                    for rental, delay in late_rental:

                        print(f"Rental ID: {rental}, Days of delay: {delay}")


                elif option == '4':
                    pass
                else:
                    print("Invalid choice!")

            elif choice == '7':
                try:
                    self._undo_service.undo()
                    print("Undo successful!")


                except Exception as re:
                    print(re)

            elif choice == '8':
                try:
                    self._undo_service.redo()
                    print("Redo successful!")
                except Exception as re:
                    print(re)
            elif choice == '9':
                break

            else:
                print("Invalid choice!")
