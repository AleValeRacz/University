package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import javafx.util.Pair;
import model.adt.MyIDictionary;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.IType;
import model.type.IntType;
import model.value.IValue;
import model.value.IntValue;

import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewLatchStatement implements IStatement{
    private String var;
    private IExpression expression;
    private Lock lock = new ReentrantLock();

    public NewLatchStatement(String var, IExpression expression)
    {
        this.var = var;
        this.expression = expression;
    }
    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        lock.lock();
        IValue number1 = expression.evaluate(state.getSymTable(), state.getHeap());
        IntValue nr1 = (IntValue) number1;
        int freeAddress = state.getLatchTable().getFreeAddress();
        state.getLatchTable().put(freeAddress, nr1.getValue());
        if (state.getSymTable().contains(var) && state.getSymTable().get(var).getType().equals(new IntType())) {
            state.getSymTable().insert(var, new IntValue(freeAddress));
        } else
            throw new StatementException("Error for variable: not defined/ does not have int type!");
        lock.unlock();
        return null;

    }

    @Override
    public IStatement deepCopy() {
        return new NewLatchStatement(this.var, this.expression.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            IType typevar = typeEnv.get(var);
            if (typevar.equals(new IntType()) && expression.typecheck(typeEnv).equals(new IntType())) {
                return typeEnv;
            } else
                throw new StatementException("NewLatchStmt: Expression or var is not of type int!");

        } catch (ExpressionException e) {
            throw new StatementException(e.getMessage());
        }
    }
    @Override
    public String toString()
        {
            return "newLatch("+ this.var+ ","+ this.expression.toString()+")";

        }


}
