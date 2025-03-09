import random
from src.domain.domain import Expense
import pickle

class BaseRepository:
    def __init__(self):
        self._history = []
        self._expenses = []
        self.generate_random_expanses()

    def generate_random_expanses(self):
        expenses = []

        types = ["food", "vacation", "ski", "travel", "clothes", "rent", "water", "gas", "animals", "school supplies", "restaurant", "gifts", "birthday party", "electricity", "shoes"]
        for i in range (10):
            day = random.randint(1,30)
            amount = random.randint(0,1000)
            type = random.choice(types)
            expenses.append(Expense(day,amount,type))


        self.update_history(expenses)
        self.save_expenses(expenses)

    def add_expense(self, expense):
        """ 
        Adds an expense to the repository
        :param expense: to be added
        :return: None
        Raises exception if expense already in repo
        """
        expenses = self.get_expenses()
        if expense in expenses:
            raise ValueError("Expense already added to repo\n")
        else:
            self.update_history(expenses)
            expenses.append(expense)
            self.save_expenses(expenses)

    def update_history(self, expenses):
        copy_expenses = []
        for expense in expenses:
            copy_expenses.append(expense)
        self._history.append(copy_expenses)

    def undo_last_operation(self):
        if not self._history:
            raise ValueError("No more undoes available.")
        else:
            last_operation = self._history.pop()
            self.save_expenses(last_operation)

    def filter_expenses(self,value):
        expenses = self.get_expenses()
        filtered_expenses = [expense for expense in expenses if expense.get_amount >= value]
        self.update_history(expenses)
        self.save_expenses(filtered_expenses)

    def get_expenses(self):
        return self._expenses

    def save_expenses(self, expenses):
        self._expenses = expenses


class TextFileRepository(BaseRepository):
    def __init__(self, filename="text_data.txt"):
        super().__init__()
        self.__filename = filename
        self._load_file()
        self._save_file()

    def _load_file(self):
        lines = []

        try:
            with open(self.__filename, "r") as file:
                lines = file.readlines()
        except IOError:
            pass

        for line in lines:
                current_line = line.split(",")
                new_expense = Expense(int(current_line[0].strip()), int(current_line[1].strip()), current_line[2].strip())
                super().add_expense(new_expense)

    def _save_file(self):
        with open(self.__filename, "w") as file:
            for expense in self.get_expenses():
                file.write(f"{expense.get_day},{expense.get_amount},{expense.get_type}\n")

    def add_expense(self, new_expense):
        super().add_expense(new_expense)
        self._save_file()

    def filter_expenses(self, value):
        super().filter_expenses(value)
        self._save_file()

    def undo_last_operation(self):
        super().undo_last_operation()
        self._save_file()

    def clear_data(self):
        with open(self.__filename, 'wt'):
            pass


class BinaryFileRepository(BaseRepository):
    def __init__(self, filename="binary_data.pkl"):
        super().__init__()
        self.filename = filename
        self._load_file()
        self._save_file()
    def _load_file(self):
        try:
            with open(self.filename, "rb") as file:
                expenses = pickle.load(file)
                self.save_expenses(expenses)
        except (FileNotFoundError, EOFError):
            pass

    def _save_file(self):
        with open(self.filename, "wb") as file:
            pickle.dump(self.get_expenses(), file)

    def add_expense(self, new_expense):
        super().add_expense(new_expense)
        self._save_file()

    def filter_expenses(self, value):
        super().filter_expenses(value)
        self._save_file()

    def undo_last_operation(self):
        super().undo_last_operation()
        self._save_file()

    def clear_data(self):
        with open(self.filename, 'wt'):
            pass








