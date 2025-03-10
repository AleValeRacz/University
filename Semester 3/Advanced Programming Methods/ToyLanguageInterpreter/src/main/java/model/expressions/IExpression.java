package model.expressions;

import exceptions.ExpressionException;
import model.adt.IHeap;
import model.adt.MyIDictionary;
import model.statements.IStatement;
import model.type.IType;
import model.value.IValue;
import model.state.PrgState;

public interface IExpression {
    IValue evaluate(MyIDictionary<String,IValue> symTbl, IHeap heap) throws ExpressionException;
    IExpression deepCopy();
    IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException;
}
