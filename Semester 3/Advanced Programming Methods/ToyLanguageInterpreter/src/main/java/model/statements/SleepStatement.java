package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expressions.ArithmeticalExpression;
import model.expressions.IExpression;
import model.expressions.RelationalExpression;
import model.expressions.ValueExpression;
import model.state.PrgState;
import model.type.BoolType;
import model.type.IType;
import model.type.IntType;
import model.value.IValue;
import model.value.IntValue;

import static model.expressions.ArithmeticalOperation.MINUS;

public class SleepStatement implements IStatement {
    IExpression number;

    public SleepStatement(IExpression number)
    {
        this.number = number;
    }

    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        IValue val = this.number.evaluate(state.getSymTable(), state.getHeap());
        int currentValue = ((IntValue) val).getValue();
        if (currentValue == 0) {
            return null;
        }
        IExpression decrementedValue = new ArithmeticalExpression(
                new ValueExpression(new IntValue(currentValue)),
                new ValueExpression(new IntValue(1)),
                MINUS);
        IStatement newSleepStatement = new SleepStatement(decrementedValue);
        state.getExecStack().push(newSleepStatement);
        state.getExecStack().push(new PrintStatement(this.number));
        return null;

    }
    @Override
    public IStatement deepCopy() {
        return new SleepStatement(this.number);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            IType typeexp = number.typecheck(typeEnv);
            if(typeexp.equals(new IntType()))
            {
                return typeEnv;
            }
            else
                throw new StatementException("Sleep: expression not of type int!");

        }catch (ExpressionException e)
        {
            throw  new StatementException(e.getMessage());
        }
    }


    @Override
    public String toString()
    {
        return "sleep("+this.number+")";
    }
}
