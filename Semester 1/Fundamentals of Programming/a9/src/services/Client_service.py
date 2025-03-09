from src.repository.Client_repository import ClientRepository
from src.repository.Exceptions import ServiceException, RepositoryException
from src.domain.client import Client
from src.services.undo_service import FunctionCall, Operation

class ClientService:
    def __init__(self, client_repository: ClientRepository, undo_service):
        self._client_repository = client_repository
        self._undo = undo_service

    def add_client(self, id, name):
            client = Client(id,name)
            try:
                self._client_repository.add_client(client)
                redo = FunctionCall(self._client_repository.add_client,client)
                undo = FunctionCall(self._client_repository.remove_client, id)
                self._undo.record(Operation(undo,redo))
                return client
            except RepositoryException as e:
                raise e

    def remove_client(self, client_id):
        try:
            client = self._client_repository.remove_client(client_id)
            redo = FunctionCall(self._client_repository.remove_client, client_id)
            undo = FunctionCall(self._client_repository.add_client, client)
            self._undo.record(Operation(undo,redo))
            return client
        except RepositoryException as e:
            raise e

    def update_client(self, id, name):
        client = self._client_repository.find_client(id)
        if client is None:
            raise RepositoryException("There's no client with this id!")
        undo = FunctionCall(self._client_repository.update_client, id, client.get_name)
        client = self._client_repository.update_client(id,name)
        redo = FunctionCall(self._client_repository.update_client, id, name)
        self._undo.record(Operation(undo,redo))
        return client


    def list_clients(self):
        return self._client_repository.get_clients()

    def search_clients(self, keyword, field):
        return self._client_repository.search_clients(keyword,field)

    def get_all_client_ids(self):
        return [client.get_id for client in self._client_repository.get_clients()]

