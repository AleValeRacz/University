package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.BoolType;
import model.type.IType;
import model.value.BoolValue;
import model.value.IValue;

public class WhileStatement implements IStatement{
    private IExpression expression;
    private IStatement statement;

    public WhileStatement(IExpression expression, IStatement statement)
    {
        this.expression = expression;
        this.statement = statement;
    }
    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        MyIStack<IStatement> stack = state.getExecStack();
        IValue valExpr = this.expression.evaluate(state.getSymTable(),state.getHeap());
        if(!valExpr.getType().equals(new BoolType()))
            throw new StatementException("Expression not of type bool!");
        BoolValue boolValue = (BoolValue) valExpr;
        if(boolValue.getValue())
        {
            stack.push(this);
            stack.push(this.statement);
        }
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new WhileStatement(this.expression.deepCopy(), this.statement.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            IType typeexp = expression.typecheck(typeEnv);
            if(typeexp.equals(new BoolType())){
                statement.typecheck(typeEnv.deepCopy());
                return typeEnv;
            }
            else
                throw new StatementException("While: The expression has not the type bool!");

        }catch (ExpressionException e)
        {
            throw  new StatementException(e.getMessage());
        }
    }

    @Override
    public String toString()
    {
        return "while("+ this.expression.toString()+")" + "{"+ this.statement.toString()+ "}";
    }
}
