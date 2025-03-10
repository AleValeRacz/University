package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.state.PrgState;
import model.type.IType;

public class CompStatement implements  IStatement{
   private  IStatement first, second;

    public CompStatement(IStatement first, IStatement second)
    {
        this.first = first;
        this.second = second;

    }

    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        state.getExecStack().push(second);
        state.getExecStack().push(first);
        return null;

    }

    @Override
    public IStatement deepCopy() {
        return new CompStatement(first.deepCopy(),this.second.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
       // MyIDictionary<String, IType> typEnv1 = this.first.typecheck(typeEnv);
       // MyIDictionary<String, IType> typEnv2 = this.second.typecheck(typeEnv);
        // return typEnv2;
        return second.typecheck(this.first.typecheck(typeEnv));
    }

    @Override
    public String toString()
    {
        return first.toString()+ ";" + second.toString();
    }
}
