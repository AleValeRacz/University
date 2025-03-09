class Expense:
    def __init__(self, day, amount, type):

        if day < 1 or day > 30:
            raise ValueError("Day must be an integer between 1 and 30!")
        if amount < 0:
            raise ValueError("Amount should be positive!")
        self._day = day
        self._amount = amount
        self._type = type
    def __str__(self):
        return "Day: " + str(self._day) + " Amount: " + str(self._amount) + " Type: " + str(self._type)
    @property
    def get_day(self):
        return self._day

    @property
    def get_amount(self):
        return self._amount

    @property
    def get_type(self):
        return self._type


