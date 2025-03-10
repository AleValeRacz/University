package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.BoolType;
import model.type.IType;

public class CondAssignStatement implements IStatement{
    private IExpression exp1, exp2, exp3;
    private String id;

    public CondAssignStatement(String id, IExpression exp1, IExpression exp2, IExpression exp3)
    {
        this.id = id;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
    }


    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        if(!state.getSymTable().contains(id))
            throw new StatementException("The variable wasn't declared previously!");
        IStatement s = new IfStatement(exp1, new AssignStatement(id,exp2), new AssignStatement(id,exp3));
        state.getExecStack().push(s);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new CondAssignStatement(this.id, this.exp1.deepCopy(), this.exp2.deepCopy(),this.exp3.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            IType typeexp1 = exp1.typecheck(typeEnv);
            IType typeexp2 = exp2.typecheck(typeEnv);
            IType typeexp3 = exp3.typecheck(typeEnv);
            IType typevar = typeEnv.get(this.id);
            if(typeexp1.equals(new BoolType())){
                if (typevar.equals(typeexp2) && typevar.equals(typeexp3))
                    return typeEnv;
                else throw new StatementException("Cond Assignment: right and left hand side have different types!");
            }
            else
                throw new StatementException("Cond Assignment: The expression does not have the type bool!");

        }catch (ExpressionException e)
        {
            throw  new StatementException(e.getMessage());
        }
    }

    @Override
    public String toString()
    {
        return this.id + "=" + this.exp1+"?"+this.exp2+":"+this.exp3;

    }
}
