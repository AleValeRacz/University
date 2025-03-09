from src.repository.memory_repository import BaseRepository
from src.domain.domain import Expense

class Services:
    def __init__(self, repo: BaseRepository):
        self._repo = repo



    def add_expense(self, day, amount, type):
        """
        Creates an expense and adds it to the list of current expenses
        :param day:int
        :param amount:int
        :param type:str
        :return:-
        Raises ValueErrors if the input data is not correct
        """
        try:
            expense = Expense(int(day), int(amount), type)
        except ValueError as e:
            raise ValueError("Invalid input!")
            pass
        expenses = self.get_all_expenses()
        if expense in expenses:
            raise ValueError("Expense already added to repo")
        else:
            self._repo.add_expense(expense)

    def get_all_expenses(self):
        return self._repo.get_expenses()

    def filter_expense (self, value):
        self._repo.filter_expenses(value)

    def undo(self):
        self._repo.undo_last_operation()










