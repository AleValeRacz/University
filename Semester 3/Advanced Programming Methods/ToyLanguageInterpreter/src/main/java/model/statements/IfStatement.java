package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.BoolType;
import model.type.IType;
import model.value.BoolValue;
import model.value.IValue;

public class IfStatement implements  IStatement{
    private IExpression condition;
    private IStatement thenStatement, elseStatement ;

    public IfStatement(IExpression expr, IStatement thenS, IStatement elseS)
    {
        this.condition = expr;
        this.thenStatement = thenS;
        this.elseStatement= elseS;
    }
    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {

        IValue val = condition.evaluate(state.getSymTable(), state.getHeap());
        if(!val.getType().equals(new BoolType())){
            throw new StatementException("The condition is not a boolean!");

        }
        if(((BoolValue)val).getValue())
        {
            state.getExecStack().push(thenStatement);

        }
        else
            state.getExecStack().push((elseStatement));
        return null;

    }

    @Override
    public IStatement deepCopy() {
        return new IfStatement(this.condition.deepCopy(), this.thenStatement.deepCopy(),this.elseStatement.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
       try {
           IType typeexp = condition.typecheck(typeEnv);
           if(typeexp.equals(new BoolType())){
               thenStatement.typecheck(typeEnv.deepCopy());
               elseStatement.typecheck(typeEnv.deepCopy());
               return typeEnv;
           }
           else
               throw new StatementException("The condition of IF has not the type bool!");

       }catch (ExpressionException e)
       {
           throw  new StatementException(e.getMessage());
       }



    }

    @Override
    public String toString(){
        return "IF("+ condition.toString()+") THEN {"+ this.thenStatement.toString()+"} ELSE {" + this.elseStatement+"}";
    }
}
