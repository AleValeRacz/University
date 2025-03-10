package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.IHeap;
import model.adt.MyIDictionary;
import model.expressions.HeapReadingExpression;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.IType;
import model.type.RefType;
import model.value.IValue;
import model.value.RefValue;

public class HeapWritingStatement implements IStatement{
    private String varName;
    private IExpression expression;

    public HeapWritingStatement(String varname, IExpression expression)
    {
        this.varName = varname;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        MyIDictionary<String, IValue> symTable = state.getSymTable();
        IHeap heap = state.getHeap();
        if(!symTable.contains(this.varName))
            throw  new StatementException("Variable "+ this.varName+ "is not defined in the Sym table!");
        IValue tableVal = symTable.get(this.varName);
        if(!(tableVal.getType() instanceof RefType))
            throw  new StatementException("The value from Symbol Table isn't of  RefType!");
        Integer adress = ((RefValue)tableVal).getAddress();
        if(!heap.exists(adress))
            throw new StatementException("Value does not exist on heap");

        IValue valExpr = this.expression.evaluate(symTable,heap);
        if(!valExpr.getType().equals(heap.get(adress).getType()))
            throw new StatementException("Expression is not of the correct type!");

        heap.set(adress, valExpr);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new HeapWritingStatement(this.varName, this.expression);

    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        try {
            IType typevar = typeEnv.get(varName);
            IType typeexp = expression.typecheck(typeEnv);
            if (typevar.equals(new RefType(typeexp)))
                return typeEnv;
            else
                throw new StatementException("Heap Writing: right and left hand side have different types!");
        }catch(ExpressionException e){
            throw new StatementException(e.getMessage());
        }
    }

    @Override
    public String toString()
    {
        return "writeHeap("+this.varName+","+ this.expression.toString()+")";
    }
}
