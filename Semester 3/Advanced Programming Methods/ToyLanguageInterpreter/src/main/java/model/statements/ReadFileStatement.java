package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.IType;
import model.type.IntType;
import model.type.RefType;
import model.type.StringType;
import model.value.IValue;
import model.value.IntValue;
import model.value.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement{
   private IExpression expression;
   private  String varName;

   public ReadFileStatement(IExpression expression, String varName)
   {
       this.expression = expression;
       this.varName  = varName;
   }
    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        if(!state.getSymTable().contains(varName))
            throw  new StatementException("The variable is not defined!");
        if(!state.getSymTable().get(varName).getType().equals(new IntType())){
            throw new StatementException("The variable is not an int type!");
        }

        IValue evalExpression = expression.evaluate(state.getSymTable(), state.getHeap());
        if(!evalExpression.getType().equals(new StringType()))
            throw new StatementException("The evaluated expression is not a string!\n");

        BufferedReader bufferedReader = state.getFileTable().get((StringValue) evalExpression);
        try
        {
            String fileLine = bufferedReader.readLine();
            if(fileLine == null)
                fileLine = "0";
            int intFileLine = Integer.parseInt(fileLine);
            state.getSymTable().insert(this.varName, new IntValue(intFileLine));
        }catch (IOException e) {
            throw new StatementException("Error reading file!\n");
        }
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new ReadFileStatement(this.expression.deepCopy(),this.varName);

    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            IType typevar = typeEnv.get(varName);
            IType typeexp = expression.typecheck(typeEnv);
            if (typeexp.equals(new StringType()))
                return typeEnv;
            else
                throw new StatementException("Read file: var not of type int!");
        }catch(ExpressionException e){
            throw new StatementException(e.getMessage());
        }
    }

    @Override
    public String toString()
    {
        return "readFile("+ this.expression.toString()+")";
    }
}
