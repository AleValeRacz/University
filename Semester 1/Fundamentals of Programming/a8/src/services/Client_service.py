from src.repository.Client_repository import ClientRepository
from src.repository.Exceptions import ServiceException, RepositoryException
from src.domain.client import Client

class ClientService:
    def __init__(self, client_repository: ClientRepository):
        self._client_repository = client_repository

    def add_client(self, id, name):
        """
        creates a client based on its id and name
        :param id: int
        :param name: str
        :return:
        raises RepoError if encountered
        """
        client = Client(id,name)
        try:
                self._client_repository.add_client(client)
        except RepositoryException as e:
                raise e

    def remove_client(self, client_id):
        """
        removes a client with a given id
        :param client_id: int
        :return: -
        raises RepositoryError if encountered
        """
        try:
            return self._client_repository.remove_client(client_id)
        except RepositoryException as e:
            raise e

    def update_client(self, id, name):
        """
        updated a name of a client
        :param id: int
        :param name: str
        :return: -
        raises RepositoryError if encountered
        """
        try:
            self._client_repository.update_client(id,name)
        except RepositoryException as e:
            raise e

    def list_clients(self):
        return self._client_repository.get_clients()

    def search_clients(self, keyword, field):
        return self._client_repository.search_clients(keyword,field)

    def get_all_client_ids(self):
        return [client.get_id for client in self._client_repository.get_clients()]

