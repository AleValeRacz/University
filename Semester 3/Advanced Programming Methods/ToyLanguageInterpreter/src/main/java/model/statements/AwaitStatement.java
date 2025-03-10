package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import javafx.util.Pair;
import model.adt.MyIDictionary;
import model.state.PrgState;
import model.type.IType;
import model.type.IntType;
import model.value.IntValue;

import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class AwaitStatement implements IStatement{
    String var;
    private static Lock lock = new ReentrantLock();

    public AwaitStatement( String var)
    {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        lock.lock();
        if(state.getSymTable().contains(var)){
            if(state.getSymTable().get(var).getType().equals(new IntType())) {
                IntValue fi = (IntValue) state.getSymTable().get(var);
                int foundIndex = fi.getValue();
                if(state.getLatchTable().getLatchTable().containsKey(foundIndex)) {
                    if(state.getLatchTable().get(foundIndex)==0){

                    } else
                        state.getExecStack().push(this);
                } else
                    throw new StatementException("Index not a key in the latch table!");
            } else
                throw  new StatementException("Index must be of type int!");

        }else
            throw  new StatementException("Index not in the SymTable!");

        lock.unlock();
        return null;
    }


    @Override
    public IStatement deepCopy() {
        return new AwaitStatement(this.var);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            if (typeEnv.get(var).equals(new IntType()))
                return typeEnv;
            else
                throw new StatementException("Acquire Stmt: var not of type int!");
        } catch (Exception e){
            throw  new StatementException(e.getMessage());
        }

    }

    @Override
    public String toString() {
        return "await(" + var + ")";
    }

}
