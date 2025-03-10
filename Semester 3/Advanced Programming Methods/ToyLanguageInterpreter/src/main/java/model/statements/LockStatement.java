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

public class LockStatement implements IStatement{
    private String var;
    private Lock lock = new ReentrantLock();

    public LockStatement(String var)
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
                throw  new StatementException("Lock: Var not in the LockTable!");
            }
            else
            {
                if(state.getLockTable().get(foundIndex) == -1)
                    state.getLockTable().update(foundIndex, state.getID());
                else
                    state.getExecStack().push(this);
            }
        }
        else throw new  StatementException("Lock:Var is not in the symbol table or isn't of type int!");
        lock.unlock();
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new LockStatement(this.var);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            if (typeEnv.get(var).equals(new IntType()))
                return typeEnv;
            else
                throw new StatementException("Lock Stmt: var not of type int!");
        } catch (Exception e){
            throw  new StatementException(e.getMessage());
        }

    }

    @Override
    public String toString()
    { return "lock("+ var + ")";}

}
