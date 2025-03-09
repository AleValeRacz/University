from src.ui.ui import Ui
from src.repository.memory_repository import BaseRepository, TextFileRepository, BinaryFileRepository

def initialize_repository(repo):
    if repo == "text_file":
        text_file_repo = TextFileRepository()
        init_repo = text_file_repo
    elif repo == "binary_file":
        binary_file_repo = BinaryFileRepository()
        init_repo = binary_file_repo
    elif repo == "memory":
        memory_repo = BaseRepository()
        init_repo = memory_repo

    return init_repo

def start():
    choice = input("Chose which type of file to use: (text_file, binary_file, memory): ")
    repo = initialize_repository(choice)
    ui = Ui(repo)
    ui.main()


start()
