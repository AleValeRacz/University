from src.repository.Exceptions import RepositoryException

class ClientRepository:
    def __init__(self):
        self._clients = []

    def check_if_present(self, id):
        """
        checks is a client is already present in the repo based on its id
        :param id: int
        :return: -
        raises RepositoryException if the movie is already in the repo
        """
        ids = []
        for client in self._clients:
            ids.append(client.get_id)
        if id in ids:
            raise RepositoryException("This client is already in the repository")

    def check_if_not_present(self, id):
        """
        checks if a movie is not present in the repo
        :param id: int
        :return:
        raises error if a movie is not in the repo
        """
        ids = []
        for client in self._clients:
            ids.append(client.get_id)
        if id not in ids:
            raise RepositoryException("This client is not in the repository")

    def add_client(self, client):
        """
        adds a client to repo
        :param client: obj from class Client
        :return: -
        """
        self.check_if_present(client.get_id)
        self._clients.append(client)

    def remove_client(self, client_id):
        """
        removes a client based on its id
        :param client_id: int
        :return: -
        """
        self.check_if_not_present(client_id)
        self._clients = [c for c in self._clients if c.get_id != client_id]

    def update_client(self, client_id, new_name):
        """
        updates the name of a client based on its id
        :param client_id: id
        :param new_name: str
        :return: -
        raises RepositoryException if the id doesn't corespond with the id of a client in the repo
        """
        ok = 0
        for client in self._clients:
            if client.get_id == client_id:
                client.set_name(new_name)
                ok = 1
        if ok == 0:
            raise RepositoryException("No client found with this id.")

    def get_clients(self):
        return self._clients

    def search_clients(self, keyword, field):
        keyword = keyword.lower()
        fields = ['id', 'name']
        if field not in fields:
            raise RepositoryException("Invalid search field")
        return [client for client in self._clients if keyword in str(getattr(client, f'get_{field}')).lower()]
