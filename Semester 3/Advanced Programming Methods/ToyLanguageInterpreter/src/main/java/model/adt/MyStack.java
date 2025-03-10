package model.adt;
import exceptions.StackException;
import model.statements.IStatement;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class MyStack<T> implements MyIStack<T> {
    Stack<T> stack;
    public MyStack(){
        this.stack = new Stack<T>();
    }

    @Override
    public T pop() throws StackException {
        if (stack.isEmpty())
            throw new StackException("Stack is empty!\n");
        return this.stack.pop();
    }

    @Override
    public void push(T t)  {
        this.stack.push(t);
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public int size() {
        return this.stack.size();
    }

    @Override
    public List<T> toList() {
        List<T> list = new ArrayList<>(stack);
        return list;
    }


    @Override
    public String toString() {
            StringBuilder str = new StringBuilder();

            for(T el: this.stack){
                str.append(el);
                str.append("\n");
            }


            return "Stack contains: " + str.toString();
        }

}
