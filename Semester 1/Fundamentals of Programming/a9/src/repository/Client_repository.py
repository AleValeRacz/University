from src.repository.Exceptions import RepositoryException
from src.domain.client import Client
import pickle
class ClientRepository:
    def __init__(self):
        self._clients = []

    def check_if_present(self, id):
        ids = []
        for client in self._clients:
            ids.append(client.get_id)
        if id in ids:
            raise RepositoryException("This client is already in the repository")

    def find_client(self, id):
        for client in self._clients:
            if client.get_id == id:
                return client
        return None

    def check_if_not_present(self, id):
        ids = []
        for client in self._clients:
            ids.append(client.get_id)
        if id not in ids:
            raise RepositoryException("This client is not in the repository")

    def add_client(self, client):
        self.check_if_present(client.get_id)
        self._clients.append(client)
        return client

    def remove_client(self, client_id):
        self.check_if_not_present(client_id)
        client = self.find_client(client_id)
        if client is not None:
            self._clients.remove(client)
            return client


    def update_client(self, client_id, new_name):
        for client in self._clients:
            if client.get_id == client_id:
                client.set_name(new_name)
                return client


    def get_clients(self):
        return self._clients

    def search_clients(self, keyword, field):
        keyword = keyword.lower()
        fields = ['id', 'name']
        if field not in fields:
            raise RepositoryException("Invalid search field")
        return [client for client in self._clients if keyword in str(getattr(client, f'get_{field}')).lower()]

    def save_clients(self, clients):
        self._clients = clients


class ClientFileRepo(ClientRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self.load_file()

    def load_file(self):
        try:
            with open(self._file_name, "r") as f:
                lines = f.readlines()
                for line in lines:
                    data = line.split(",")
                    data = [elem.strip() for elem in data]
                    id = int(data[0])
                    name = str(data[1])
                    client = Client(id,name)
                    super().add_client(client)
        except ValueError:
            pass


    def load_file(self):
        with open(self._file_name, "r") as f:
            lines = f.readlines()
            for line in lines:
                data = line.split(",")
                data = [elem.strip() for elem in data]
                client = Client(data[0],[data[1]])
                super().add_client(client)

    def save_file(self):
        with open(self._file_name, "w") as f:
            for client in super().get_clients():
                f.write(f"{client.get_id},{client.get_name}\n")

    def add_client(self, client):
        super().add_client(client)
        self.save_file()

    def remove_client(self, id):
        super().remove_client(id)
        self.save_file()

    def update_client(self,id, name):
        super().update_client(id,name)
        self.save_file()


class ClientBinaryRepo(ClientRepository):
        def __init__(self, clients_file):
            super().__init__()
            self._clients_file = clients_file
            self.__load()

        def __load(self):
            try:
                with open(self._clients_file, "rb") as f:
                    clients = pickle.load(f)
                    super().save_clients(clients)
            except (EOFError,FileNotFoundError):
                pass

        def save_file(self):
            try:
                clients = open(self._clients_file, "wb")
                pickle.dump(super().get_clients(), clients)
            except IOError:
                raise RepositoryException("File error!")

        def add_client(self, client):
            super().add_client(client)
            self.save_file()

        def remove_client(self, id):
            super().remove_client(id)
            self.save_file()

        def update_client(self,id, name):
            super().update_client(id,name)
            self.save_file()





