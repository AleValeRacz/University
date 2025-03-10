package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import javafx.util.Pair;
import model.adt.IHeap;
import model.adt.ISemaphoreTable;
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

public class CreateSemStatement implements IStatement {

    private String var;
    private IExpression expression;
    private Lock lock = new ReentrantLock();

    public CreateSemStatement(String var, IExpression expression) {
        this.var = var;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        this.lock.lock();
        MyIDictionary<String, IValue> symTable = state.getSymTable();
        IHeap heap = state.getHeap();
        ISemaphoreTable semTable = state.getSemaphoreTable();
        IValue number1 = expression.evaluate(state.getSymTable(), state.getHeap());
        IntValue nr1 = (IntValue) number1;
        int freeAddress = semTable.getFreeAddress();
        semTable.put(freeAddress, new Pair<>(nr1.getValue(), new ArrayList<>()));
        if (symTable.contains(var) && symTable.get(var).getType().equals(new IntType())) {
            symTable.insert(var, new IntValue(freeAddress));
        } else
            throw new StatementException("Error for variable: not defined/ does not have int type!");
        lock.unlock();
        return null;


    }

    @Override
    public IStatement deepCopy() {
        return new CreateSemStatement(this.var, this.expression.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
                IType typevar = typeEnv.get(var);
                if(typevar.equals(new IntType()) && expression.typecheck(typeEnv).equals(new IntType()))
                {
                    return typeEnv;
                }
                else
                    throw  new StatementException("SemCreate: Expression or var is not of type int!");

            } catch (ExpressionException e) {
                throw new StatementException(e.getMessage());
            }

    }
    @Override
    public String toString() {
        return "CreateSemaphore (" + var + "," + expression + ")";
    }
}

