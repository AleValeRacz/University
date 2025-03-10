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

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStatement implements IStatement{
   private IExpression expression;

   public CloseRFileStatement(IExpression expression)
   {
       this.expression = expression;
   }
    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        IValue evalExpression = this.expression.evaluate(state.getSymTable(), state.getHeap());
        if (!evalExpression.getType().equals(new StringType())){
            throw  new StatementException("The expression is not a string type!");
        }
        StringValue stringVal = (StringValue) evalExpression;
        BufferedReader reader = state.getFileTable().get(stringVal);
        if(reader == null){
            throw new StatementException("No file is opened with this name!");
        }
        try{
            reader.close();
        }catch (IOException e) {
            throw new StatementException(e.getMessage());

        }
        state.getFileTable().remove(stringVal);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new CloseRFileStatement(this.expression.deepCopy());
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
        return "closeRFile("+ this.expression.toString()+")";
    }
}
