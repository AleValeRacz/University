import random
class Client:
    def __init__(self, client_id, name):
        self.__client_id = client_id
        self.__name = name

    @property
    def get_id(self):
        return self.__client_id

    @property
    def get_name(self):
        return self.__name

    def set_name(self, name):
        self.__name = name

    def __str__(self):
        return f" ID: {self.__client_id}; Name: {self.__name}"

def generate_clients(nr):
        id = 200
        clients = []
        name_list = ["Ana", "Maria", "Bogdan", "Alexandra", "Marius", "Alex", "Simona", "Adrian", "Valentina", "Mihai", "Andrei", "Teodora", "Corina", "George", "Roxana", "Antonia", "Florin", "Gabriel", "Larisa", "Denisa"]
        for i in range(nr):
            clients.append(Client(id,random.choice(name_list)))
            id += 1
        return clients
