package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.IType;
import model.type.StringType;
import model.value.IValue;
import model.value.StringValue;

import java.beans.Expression;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class OpenRFileStatement implements  IStatement{

    private IExpression expression;

    public OpenRFileStatement(IExpression expression)
    {
        this.expression = expression;
    }
    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        IValue evalExpression = this.expression.evaluate(state.getSymTable(), state.getHeap());
        if (!evalExpression.getType().equals(new StringType()))
            throw new StatementException("The expression is not a string type!");

        StringValue stringVal = (StringValue) evalExpression;
        if(state.getFileTable().contains(stringVal))
            throw new StatementException("File is already opened!");

        try {
            BufferedReader reader = new BufferedReader(new FileReader(stringVal.getValue()));
            state.getFileTable().insert(stringVal, reader);
        } catch(IOException e){
            throw new StatementException(e.getMessage());
        }
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new OpenRFileStatement(expression.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            expression.typecheck(typeEnv);
            return typeEnv;
        }catch(ExpressionException e){
            throw new StatementException(e.getMessage());
        }
    }

    @Override
    public String toString()
    {
        return "openRFile("+ this.expression.toString()+")";
    }
}
