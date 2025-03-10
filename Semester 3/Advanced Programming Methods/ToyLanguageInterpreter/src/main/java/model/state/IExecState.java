package model.state;

import exceptions.StackException;
import model.statements.IStatement;

public interface IExecState {
    public void push(IStatement statement);
    public IStatement pop() throws StackException;
    int size();
    boolean isEmpty();
}