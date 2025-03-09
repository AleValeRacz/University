#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
import functions
from datetime import date
import copy
def process_command_add(command,transactions, history):
    if len(command) != 4:
        print("This in an invalid command!")
        return transactions
    if command[2] not in ["in", "out"]:
        print("This is an invalid command!")
        return transactions
    current_day = date.today().day
    history.append(copy.deepcopy(transactions))
    transactions = functions.add_transaction(transactions,current_day,command[1],command[2],command[3])
    return transactions

def process_insert_command(command,transactions, history):
    if len(command) != 5:
        print("This in an invalid command!")
        return transactions
    if command[3] not in ["in", "out"]:
        print("Invalid command!")
        return transactions
    history.append(copy.deepcopy(transactions))
    transactions = functions.add_transaction(transactions,command[1], command[2], command[3], command[4])
    return transactions

def process_remove_command(command,transactions, history):
    original_transactions = copy.deepcopy(transactions)
    if len(command) == 2:
        try:
            command[1] = int(command[1])
        except ValueError:
            if command[1] not in ["in", "out"]:
                print("This is an invalid command!")
                return transactions
            transactions = functions.remove_based_on_type(transactions, command[1])
            if transactions != original_transactions:
                history.append(copy.deepcopy(original_transactions))
            return transactions
        transactions = functions.remove_transactions_between_days(transactions,int(command[1]),int(command[1]))
        if transactions != original_transactions:
            history.append(copy.deepcopy(original_transactions))
        return transactions
    if len(command) == 4:
        if command[2] != "to":
            print("This is an invalid command!")
            return transactions
        try:
            command[1] = int(command[1])
            command[3] = int(command[3])
        except ValueError:
            print("Invalid command!The given days should be integer values!")
            return transactions
        transactions = functions.remove_transactions_between_days(transactions, int(command[1]), int(command[3]))
        if transactions != original_transactions:
            history.append(copy.deepcopy(original_transactions))
        return transactions
    else:
        print("This is an invalid command!")
        return transactions

def process_replace_command(command,transactions, history):
    original_transactions = copy.deepcopy(transactions)
    if len(command) == 6:
        try:
            command[1] = int(command[1])
            command[5] = int(command[5])
        except ValueError:
            print("Invalid values for day or replacement amount!")
            return
        if command[5] < 0:
            print("Invalid given value!")
            return
        if command[2] not in ["in", "out"]:
            print("This is not a valid type!")
            return
        if command[4] != "with":
            print("This is an invalid command!")
            return
        transactions = functions.replace_amount(transactions,command[1],command[2], command[3], command[5])
        if transactions != original_transactions:
            history.append(copy.deepcopy(original_transactions))
        return transactions
    else:
        print("This is an invalid command")
        return transactions

def list_transactions(transactions):
    #print(*transactions, sep = "\n")
    for transaction in transactions:
        print(f"{functions.get_day(transaction)} {functions.get_amount_money(transaction)} {functions.get_type(transaction)} {functions.get_description(transaction)}")

def process_display_command(command, transactions):
    if len(command) == 1:
        list_transactions(transactions)
        return
    signs = ["=", "<", ">"]
    if len(command) == 2:
        if command[1] in ["in", "out"]:
            new_transactions = functions.filter_on_type(transactions,command[1])
            list_transactions(new_transactions)
            return
        else:
            print("This is an invalid command")
            return
    if len(command) == 3:
        if command[1] == "balance":
            try:
                command[2] = int(command[2])
            except ValueError:
                print("Invalid value for day!")
                return
            balance = functions.compute_balance(transactions,command[2])
            print(balance)
        else:
            try:
                command[2] = int(command[2])
            except ValueError:
                print("Invalid value!")
                return
            if command[1] not in signs:
                print("This is an invalid command!")
                return
            else:
                list_transactions(functions.find_transactions_that_satisfy_the_condition(transactions,int(command[2]),signs.index(command[1])))
def process_command_filter(command,transactions, history):
    original_transactions = copy.deepcopy(transactions)
    if len(command) == 2:
        if command[1] not in ["in", "out"]:
            print("This is an invalid command!")
            return transactions
        else:
            transactions = functions.filter_on_type(transactions,command[1])
            if transactions != original_transactions:
                history.append(copy.deepcopy(original_transactions))
            return transactions
    if len(command) == 3:
        if command[1] not in ["in", "out"]:
            print("This is an invalid command!")
            return transactions
        try:
            command[2] = int(command[2])
        except ValueError:
            print("Invalid value!")
            return transactions
        transactions = functions.filter_on_type_and_amount(transactions,command[1], command[2])
        if transactions != original_transactions:
            history.append(copy.deepcopy(original_transactions))
        return transactions

def process_undo_command(command, transactions, history):
    if len(command) != 1:
        print("This is an invalid command!")
        return transactions
    if len(history) > 0:
        transactions = history.pop()
        return transactions
    else:
        print("No operation to undo!")
        return transactions

def process_command(command, transactions, history):
    commands = ["add", "insert", "remove", "replace", "list", "filter", "undo"]
    if command[0] not in commands:
        print("Invalid command")
    if command[0] == "add":
        transactions = process_command_add(command,transactions,history)
    elif command[0] == "insert":
        transactions = process_insert_command(command, transactions,history)
    elif command[0] == "remove":
        transactions = process_remove_command(command,transactions,history)
    elif command[0] == "replace":
        transactions = process_replace_command(command,transactions,history)
    elif command[0] == "list":
        process_display_command(command,transactions)
    elif command[0] == "filter":
        transactions = process_command_filter(command,transactions,history)
    elif command[0] == "undo":
        transactions = process_undo_command(command, transactions,history)
    return transactions

def print_menu():
    print(""" Hello John! What would you like to do?
        add <value> <type> <description>
        insert <day> <value> <type> <description>
        remove <day>
        remove <start day> to <end day>
        remove <type>
        replace <day> <type> <description> with <value>
        list
        list <type>
        list [ < | = | > ] <value>
        list balance <day>
        filter <type>
        filter <type> <value>
        undo
    """
    )
def run():
    transactions = functions.generate_random_transactions(10)
    history = []
    while True:
        print_menu()
        command = input("Enter a command, please: ")
        command = command.strip()
        if command == "exit":
            return
        if command == "":
            continue
        command = command.split()
        transactions = process_command(command,transactions, history)






