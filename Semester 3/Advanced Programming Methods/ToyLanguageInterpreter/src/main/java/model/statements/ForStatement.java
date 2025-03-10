package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expressions.IExpression;
import model.expressions.RelationalExpression;
import model.expressions.VariableExpression;
import model.state.PrgState;
import model.type.BoolType;
import model.type.IType;
import model.type.IntType;

public class ForStatement implements IStatement{
    private IExpression exp1, exp2, exp3;
    private String v;
    private IStatement stmt;

    public ForStatement(String v,IExpression exp1, IExpression exp2, IExpression exp3, IStatement stmt)
    {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
        this.v = v;
        this.stmt = stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        IStatement s =  new CompStatement(
                new VarDeclStatement(this.v, new IntType()),
                new CompStatement(
                        new AssignStatement(this.v, exp1),
                        new WhileStatement(
                                new RelationalExpression(new VariableExpression(this.v), exp2, "<"),
                                new CompStatement(stmt, new AssignStatement(this.v, exp3)))));
        state.getExecStack().push(s);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new ForStatement("v", this.exp1.deepCopy(),this.exp2.deepCopy(),this.exp3.deepCopy(),stmt.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            typeEnv.insert(v, new IntType());
            IType typeexp1 = exp1.typecheck(typeEnv);
            IType typeexp2 = exp2.typecheck(typeEnv);
            IType typeexp3 = exp3.typecheck(typeEnv);
            if(typeexp1.equals(new IntType()) && typeexp2.equals(new IntType()) && typeexp3.equals(new IntType()))
            {
                    typeEnv.remove(v);
                    return typeEnv;
            }
            else
                throw new StatementException("For:some of the variables are not of type int!");

        }catch (ExpressionException e)
        {
            throw  new StatementException(e.getMessage());
        }
    }

    @Override
    public String toString()
    {
        return "for("+this.v+ "="+ this.exp1+";"+ this.v+ "<"+ this.exp2+";"+ this.v+ "="+ this.exp3+")"+ this.stmt;

    }
}
