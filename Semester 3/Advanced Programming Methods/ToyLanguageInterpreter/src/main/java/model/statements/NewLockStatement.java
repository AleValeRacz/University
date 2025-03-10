package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.IType;
import model.type.IntType;
import model.value.IntValue;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewLockStatement implements IStatement{
    private String var;
    private Lock lock = new ReentrantLock();

    public NewLockStatement(String var){
        this.var = var;
    }
    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        lock.lock();
        int freeAddress = state.getLockTable().getFreeAddress();
        state.getLockTable().put(freeAddress, -1);
        if (state.getSymTable().contains(var) && state.getSymTable().get(var).getType().equals(new IntType()))
        {
            state.getSymTable().insert(var, new IntValue(freeAddress));
        }
        else throw new  StatementException("NewLock: Var is not in the symbol table or isn't of type int!");
        lock.unlock();
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new NewLockStatement(this.var);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            if (typeEnv.get(var).equals(new IntType()))
                return typeEnv;
            else
                throw new StatementException("newLock Stmt: var not of type int!");
        } catch (Exception e){
            throw  new StatementException(e.getMessage());
        }

    }

    @Override
    public String toString()
    { return "newLock("+ var + ")";}
}
