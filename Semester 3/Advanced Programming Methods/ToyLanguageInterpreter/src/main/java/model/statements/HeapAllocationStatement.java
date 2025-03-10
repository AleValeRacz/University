package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.IHeap;
import model.adt.MyIDictionary;
import model.expressions.IExpression;
import model.state.PrgState;
import model.type.IType;
import model.type.RefType;
import model.value.IValue;
import model.value.RefValue;

public class HeapAllocationStatement implements IStatement{
   private String varName;
   private IExpression expression;

   public HeapAllocationStatement(String varName, IExpression expression)
   {
       this.varName = varName;
       this.expression = expression;
   }


    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {
        MyIDictionary<String, IValue>  symTable = state.getSymTable();
        IHeap  heap = state.getHeap();
        if(!symTable.contains(varName))
        {
            throw new StatementException("There is no variable" + varName+ "in the symbol table");
        }
        IValue variableValue = symTable.get(this.varName);
        if(!(variableValue.getType() instanceof RefType)){
            throw new StatementException("Variable is not a Ref type!");
        }

        IValue value = expression.evaluate(symTable,heap);
        if(!value.getType().equals( ((RefType) variableValue.getType()).getInner())){
            throw new StatementException("The expression is a different type compared to the referenced type!");

        }
        int address = heap.allocate(value);
        symTable.insert(varName, new RefValue(address,((RefValue) variableValue).getLocationType()));
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new HeapAllocationStatement(this.varName, this.expression);

    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
       try {
           IType typevar = typeEnv.get(varName);
           IType typeexp = expression.typecheck(typeEnv);
           if (typevar.equals(new RefType(typeexp)))
               return typeEnv;
           else
               throw new StatementException("Heap Alloc: right and left hand side have different types!");
       }catch(ExpressionException e){
           throw new StatementException(e.getMessage());
       }
    }

    @Override
    public String toString()
    {
        return "new(" + this.varName +","+this.expression+")";
    }


}
