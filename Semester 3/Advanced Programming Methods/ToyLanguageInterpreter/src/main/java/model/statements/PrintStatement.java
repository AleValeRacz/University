package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.IType;
import model.value.IValue;


public class PrintStatement implements IStatement {
    private IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState state) throws ExpressionException {
        IValue val = expression.evaluate(state.getSymTable(), state.getHeap());
        state.getOutputList().add(val.toString());
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new PrintStatement(this.expression.deepCopy());

    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
      try {
          expression.typecheck(typeEnv);
          return typeEnv;
      }catch(ExpressionException e){
          throw new StatementException("Print stmt:" + e.getMessage());
        }

    }

    @Override
    public String toString() {
        return "print(" +this.expression.toString()+")";
    }
}
