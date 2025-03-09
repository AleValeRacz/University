class FunctionCall:
    def __init__(self, name, *params):
        self.__name = name
        self.__params = params

    def call(self):
        return self.__name(*self.__params)

    def __call__(self, *args, **kwargs):
        return self.call()


class Operation:
    def __init__(self, fc_undo: FunctionCall, fc_redo: FunctionCall):
        self.__undo = fc_undo
        self.__redo = fc_redo

    def undo(self):
        self.__undo()

    def redo(self):
        self.__redo()


class UndoError(Exception):
    pass


class UndoService:
    def __init__(self):
        self.__history = []
        self.__index = 0

    def record(self, oper: Operation):
        self.__history.insert(0, oper)

    def undo(self):
        if self.__index == len(self.__history):
            raise UndoError("No more undos")

        self.__history[self.__index].undo()
        self.__index += 1

    def redo(self):
        if self.__index == 0:
            raise UndoError("No more redos")

        self.__index -= 1
        self.__history[self.__index].redo()
