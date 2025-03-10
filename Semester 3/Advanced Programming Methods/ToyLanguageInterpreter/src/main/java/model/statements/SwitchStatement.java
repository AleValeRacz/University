package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.expressions.IExpression;
import model.expressions.RelationalExpression;
import model.state.PrgState;
import model.type.IType;
import model.type.RefType;

public class SwitchStatement implements IStatement {
    private IExpression exp, exp1, exp2;
    private IStatement stmt1, stmt2, stmt3;

    public SwitchStatement(IExpression exp, IExpression exp1, IStatement stmt1, IExpression exp2, IStatement stmt2, IStatement stmt3)
    {
        this.exp = exp;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.stmt1 = stmt1;
        this.stmt2 = stmt2;
        this.stmt3 = stmt3;
    }
    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        IExpression e1 = new RelationalExpression(exp, exp1, "==");
        IExpression e2 = new RelationalExpression(exp, exp2, "==");
        IStatement s = new IfStatement(e1, stmt1, new IfStatement(e2, stmt2, stmt3));
        MyIStack<IStatement> stack = state.getExecStack();
        stack.push(s);
        return null;
    }
    @Override
    public IStatement deepCopy() {
        return new SwitchStatement(this.exp.deepCopy(), this.exp1.deepCopy(), this.stmt1.deepCopy(),this.exp2.deepCopy(),this.stmt2.deepCopy(),this.stmt3.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            IType typeexp = exp.typecheck(typeEnv);
            IType typeexp1 = exp1.typecheck(typeEnv);
            IType typeexp2 = exp2.typecheck(typeEnv);
            if (typeexp.equals(typeexp1) && typeexp.equals(typeexp2))
                return typeEnv;
            else
                throw new StatementException("SwitchStatement: Expressions are not of the same type!");
        }catch(ExpressionException e){
            throw new StatementException(e.getMessage());
        }

    }

    @Override
    public String toString()
    {
        return "switch("+ this.exp+ ") (case "+ this.exp1+ ": "+ this.stmt1+ ") (case "+ this.exp2+ ": "+ this.stmt2+ ") (default: "+ this.stmt3+ ")";

    }
}
