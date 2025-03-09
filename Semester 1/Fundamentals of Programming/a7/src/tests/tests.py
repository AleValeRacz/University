from src.repository.memory_repository import BaseRepository
from src.services.services import Services

class Test:
    def __init__(self, repo):
        self._repo_instance = repo()
        self._service = Services(self._repo_instance)

    def test_generate_services(self):
        assert len(self._service.get_all_expenses()) == 10

    def test_add_expense(self):
        self._service.add_expense(10,300,"party")
        assert len(self._service.get_all_expenses()) == 11
        try:
            self._service.add_expense(33,40,"going_out")
        except ValueError:
            pass
        assert len(self._service.get_all_expenses()) == 11

        try:
            self._service.add_expense(30, "no", "party")
        except ValueError:
            pass
        assert len(self._service.get_all_expenses()) == 11

    def test_all(self):
        self.test_generate_services()
        self.test_add_expense()

test = Test(BaseRepository)
test.test_all()
