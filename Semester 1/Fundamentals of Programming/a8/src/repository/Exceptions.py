class RepositoryException(Exception):
    def __init__(self, message):
        self._message = message

    def get_message(self):
        return self._message

    def __str__(self):
        return self._message


class ServiceException(Exception):
    def __init__(self, message):
        self._message = message

    def get_message(self):
        return self._message

    def __str__(self):
        return self._message

class EntityNotFoundError(Exception):
    def __init__(self, entity_name, entity_id):
        self.__entity_name = entity_name
        self.__entity_id = entity_id

    def __str__(self):
        return self.__entity_name + " with id " + str(self.__entity_id) + " not found"

