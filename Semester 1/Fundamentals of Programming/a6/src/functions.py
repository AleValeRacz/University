#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#

import random
from datetime import date

def create_transaction(day, amount, type, description):
    """
    Function creates a transaction based on its day of month, amount of mony, type(in or out) and description
    :param day: int
    :param amount: int
    :param type: string
    :param description: string
    :return: a transaction with the given parameters as elements in the dictionary
    """
    return {
        "day": day,
        "amount_of_money": amount,
        "type": type,
        "description": description
    }


def get_day(transaction):
    return int(transaction["day"])


def get_amount_money(transaction):
    return int(transaction["amount_of_money"])


def get_type(transaction):
    return transaction["type"]


def get_description(transaction):
    return transaction["description"]


def set_amount(transaction, value):
    transaction["amount_of_money"] = value
    return transaction


def validate_transaction(transaction):
    """
    Function checks if the input data for the transaction are valid
    :param transaction:
    :return: -, if the elements of the transaction are valid
    :raises: Exception with str message otherwise:
                "Invalid day!\n" if the day isn't in the 1-30 interval
                "Invalid amount of money!\n" if the amount of money is not a positive value
                "Invalid type!\n" if the type is not either in or out
                "Invalid description\n" if the description is empty
    """
    errors = ""
    if get_day(transaction) > 30 or get_day(transaction) < 1 or type(get_day(transaction)) is not int:
        errors += "Invalid day!\n"
    if get_amount_money(transaction) <= 0 or type(get_amount_money(transaction)) is not int:
        errors += "Invalid amount of money!\n"
    if get_type(transaction) not in ["in", "out"]:
        errors += "Invalid type!\n"
    if get_description(transaction) == "":
        errors += "Invalid description\n"
    if len(errors) > 0:
        raise Exception(errors)


def generate_random_transactions(number_transactions):
    transactions = []

    for i in range(number_transactions):
        days = list(range(1, 31))
        amount = random.randint(1, 1000)
        type = random.choice(["in", "out"])
        description = ''.join(random.choices('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789', k=8))
        transaction = create_transaction(random.choice(days), amount, type, description)
        transactions.append(transaction)

    return transactions


def add_transaction(transactions, day, amount, type, description):
    """
    Adds a new transaction to an existing list of transactions
    :param transactions:a list of transactions
    :param day: int
    :param amount: int
    :param type: str, either "in" or "out"
    :param description: str
    :return: the updated list of transactions
    """
    transaction = create_transaction(day, amount, type, description)
    validate_transaction(transaction)
    transactions.append(transaction)
    return transactions


def remove_transactions_between_days(transactions, start_day, end_day):
    """
    functions deletes all the transactions that don't have the 'day' value between the given start day and end day
    :param transactions: list of all transactions
    :param start_day: int
    :param end_day: int
    :return: the updated list of transactions
    """
    new_transactions = []
    for transaction in transactions:
        if get_day(transaction) < start_day or get_day(transaction) > end_day:
            new_transactions.append(transaction)
    return new_transactions


def remove_based_on_type(transactions, given_type):
    """
    Function deletes from the list all the transactions that are not of the given type
    :param transactions: list of transactions
    :param given_type: str, either "in" or "out"
    :return: updated list
    """
    new_transactions = []
    for transaction in transactions:
        if get_type(transaction) != given_type:
            new_transactions.append(transaction)
    return new_transactions


def replace_amount(transactions, day, type, description, value):
    """
    Function replaces the value in "amount_of_money", of the transaction with the "day" day, "type" type, "description" description with a given value
    :param transactions: list of transactions
    :param day: int
    :param type: str, either "in" or "out"
    :param description: str
    :param value: int
    :return: the updated list
    """
    new_transactions = []
    for transaction in transactions:
        if get_day(transaction) == day and get_type(transaction) == type and get_description(
                transaction) == description:
            new_transaction = set_amount(transaction, value)
            new_transactions.append(new_transaction)
        else:
            new_transactions.append(transaction)
    return new_transactions


def compare_based_on_condition(index, value, given_value):
    if index == 0:
        return value == given_value
    if index == 1:
        return value < given_value
    return value > given_value


def find_transactions_that_satisfy_the_condition(transactions, amount, index):
    good_transactions = []
    for transaction in transactions:
        if compare_based_on_condition(index, get_amount_money(transaction), amount):
            good_transactions.append(transaction)
    return good_transactions


def compute_balance(transactions, day):
    balance = 0
    for transaction in transactions:
        if get_day(transaction) <= day:
            if get_type(transaction) == "in":
                balance += get_amount_money(transaction)
            else:
                balance -= get_amount_money(transaction)
    return balance


def filter_on_type(transactions, type):
    new_transactions = []
    for transaction in transactions:
        if get_type(transaction) == type:
            new_transactions.append(transaction)
    return new_transactions


def filter_on_type_and_amount(transactions, type, amount):
    new_transactions = []
    for transaction in transactions:
        if get_type(transaction) == type and get_amount_money(transaction) <= amount:
            new_transactions.append(transaction)
    return new_transactions

def test_create_transaction():
    #print("starting domain tests...")
    day = 2
    amount = 20
    type = "in"
    descr = "pizza"
    transaction = create_transaction(day, amount, type, descr)
    assert get_day(transaction) == day
    assert get_amount_money(transaction) == amount
    assert get_type(transaction) == type
    assert get_description(transaction) == descr
    #print("finishing domain tests...")

def test_validate_transaction():
    #print("Starting validation tests...")
    day = 45
    amount = -7
    type = "no"
    descr = ""
    transaction = create_transaction(day, amount, type, descr)
    try:
        validate_transaction(transaction)
        assert False
    except Exception as ex:
        assert str(ex) == "Invalid day!\nInvalid amount of money!\nInvalid type!\nInvalid description\n"
    #print("Finishing validation tests...")

def test_add_transaction():
    current_day = date.today().day
    transactions = [create_transaction(13,450,"out","present")]
    transactions = add_transaction(transactions,current_day,120,"in", "pizza")
    expected_transactions = [create_transaction(13,450,"out","present"),create_transaction(current_day,120,"in", "pizza") ]
    assert (expected_transactions == transactions)
    #print("finishing add test...")

def test_remove_transactions_between_days():
    t1 = create_transaction(12, 45, "out","movie")
    t2 = create_transaction(18, 100, "in", "transfer")
    t3 = create_transaction(25,140,"out","kids")
    transactions = [t1, t2, t3]
    transactions = remove_transactions_between_days(transactions,11, 18)
    expected_transactions = [t3]
    assert(len(transactions) == 1)
    assert(transactions == expected_transactions)
    #print("finished remove days")

def test_replace_amount():
    t1 = create_transaction(12, 45, "out","movie")
    t2 = create_transaction(18, 100, "in", "transfer")
    t3 = create_transaction(25,140,"out","kids")
    transactions = [t1, t2, t3]
    new_t2 = create_transaction(18, 300, "in", "transfer")
    expected_transactions = [t1,new_t2,t3]
    transactions = replace_amount(transactions,18,"in","transfer",300)
    assert(transactions == expected_transactions)
    #print("finish replace test")
def run_tests():
    test_create_transaction()
    test_validate_transaction()
    test_add_transaction()
    test_add_transaction()
    test_remove_transactions_between_days()
    test_replace_amount()


run_tests()
