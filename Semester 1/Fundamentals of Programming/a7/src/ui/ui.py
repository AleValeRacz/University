from src.services.services import Services

class Ui:
    def __init__(self, repo):
        self._service = Services(repo)

    def main(self):
        while True:
            print("""               Menu
            1. Add an expense.
            2. Display the list of expenses.
            3. Filter the list so that it contains only expenses above a certain value read from the console.     
            4. Undo the last operation that modified program data.
            5. Exit
            """
            )
            choice = input("Enter your choice: ")
            if choice == '1':
                try:
                    day = int(input("Enter a day of the month: "))
                    amount = int(input("Enter the amount of money: "))
                    type = input("Enter the type of the expense: ")
                    self._service.add_expense(day,amount,type)
                except ValueError as e:
                    print(e)
            elif choice == '2':
                expenses = self._service.get_all_expenses()
                for expense in expenses:
                    print(expense)
            elif choice == '3':
                try:
                    value = int(input("enter a value to compare with:"))
                    self._service.filter_expense(value)
                except ValueError:
                    print("Invalid input for value!")
            elif choice == '4':
                try:
                    self._service.undo()
                except ValueError as e:
                    print(e)
            elif choice == '5':
                print("Exiting the application.Goodbye!")
                return
            else:
                print("Invalid input!Please try again!")



