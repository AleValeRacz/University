package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.state.PrgState;
import model.type.IType;
import model.type.IntType;
import model.value.IntValue;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class UnlockStatement implements IStatement{
    private String var;
    private Lock lock = new ReentrantLock();

    public UnlockStatement(String var)
    {
        this.var = var;
    }
    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        lock.lock();
        if (state.getSymTable().contains(var) && state.getSymTable().get(var).getType().equals(new IntType()))
        {
            IntValue fi = (IntValue) state.getSymTable().get(var);
            int foundIndex = fi.getValue();
            if(!state.getLockTable().getLockTable().containsKey(foundIndex))
            {
                throw  new StatementException("Unlock: Var not in the LockTable!");
            }
            else
            {
                if(state.getLockTable().get(foundIndex) == state.getID())
                    state.getLockTable().update(foundIndex, -1);
            }
        }
        else throw new  StatementException("Var is not in the symbol table or isn't of type int!");
        lock.unlock();
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new UnlockStatement(this.var);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            if (typeEnv.get(var).equals(new IntType()))
                return typeEnv;
            else
                throw new StatementException("Unlock Stmt: var not of type int!");
        } catch (Exception e){
            throw  new StatementException(e.getMessage());
        }

    }
    @Override
    public String toString()
    { return "unlock("+ var + ")";}


}
