package model.expressions;

import exceptions.ExpressionException;
import model.adt.IHeap;
import model.adt.MyIDictionary;
import model.type.IType;
import model.type.RefType;
import model.value.IValue;
import model.value.RefValue;

import java.beans.Expression;

public class HeapReadingExpression implements IExpression {

    private IExpression expression;

    public HeapReadingExpression(IExpression expression)
    {
        this.expression = expression;
    }
    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symTbl, IHeap heap) throws ExpressionException {
        IValue val = this.expression.evaluate(symTbl,heap);
        if( !(val instanceof RefValue)) {
               throw new ExpressionException("Expression is not a Ref Value!");
        }
        Integer address = ((RefValue) val).getAddress();
        if(!heap.exists(address))
        {
            throw new ExpressionException("The value is not in the Heap table!");
        }
        return heap.get(address);
    }

    @Override
    public IExpression deepCopy() {
        return new HeapReadingExpression(this.expression.deepCopy());
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException {
        IType typ = expression.typecheck(typeEnv);
        if(typ instanceof RefType){
            RefType reft = (RefType) typ;
            return reft.getInner();
        }else
            throw  new ExpressionException("the heap reading argument is not a RefType");
    }

    @Override
    public String toString()
    {
        return "readHeap("+this.expression+")";
    }
}
