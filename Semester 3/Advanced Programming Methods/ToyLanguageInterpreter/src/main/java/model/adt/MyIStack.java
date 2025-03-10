package model.adt;

import exceptions.StackException;

import java.util.List;

public interface MyIStack<T> {
    T pop()throws StackException;
    void push(T t);
    boolean isEmpty();
    int size();
    public List<T> toList();

}
