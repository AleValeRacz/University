package model.expressions;

import exceptions.ExpressionException;
import model.adt.IHeap;
import model.adt.MyIDictionary;
import model.type.BoolType;
import model.type.IType;
import model.type.IntType;
import model.value.BoolValue;
import model.value.IValue;
import model.value.IntValue;



public class RelationalExpression implements IExpression{

    private IExpression left;
    private IExpression right;
    String operator;

    public RelationalExpression(IExpression left, IExpression right,
                                  String operator){
        this.left = left;
        this.right = right;
        this.operator = operator;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symTbl, IHeap heap) throws ExpressionException {

        IValue leftValue = left.evaluate(symTbl,heap);
        IValue rightValue = right.evaluate(symTbl,heap);

        if(!leftValue.getType().equals(new IntType())
                || !rightValue.getType().equals(new IntType())){
            throw new ExpressionException("Invalid expressions");
        }

        int intLeftValue = ((IntValue) leftValue).getValue();
        int intRightValue = ((IntValue) rightValue).getValue();

        switch(operator){
            case "<"-> {
                return new BoolValue(intLeftValue < intRightValue);
            }

            case ">" -> {
                return new BoolValue(intLeftValue>intRightValue);
            }
            case "<=" -> {
                return new BoolValue(intLeftValue<=intRightValue);
            }
            case ">=" -> {
                return new BoolValue(intLeftValue>=intRightValue);
            }
            case "==" -> {
                return new BoolValue(intLeftValue==intRightValue);
            }
            case "!=" -> {
                return new BoolValue(intLeftValue!= intRightValue);
            }

            default -> {
                throw new ExpressionException("Invalid operation");
            }
        }


    }

    @Override
    public IExpression deepCopy() {
        return new RelationalExpression(this.left.deepCopy(),this.right.deepCopy(),this.operator);
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException {
        IType typ1 = this.left.typecheck(typeEnv);
        IType typ2 = this.right.typecheck(typeEnv);
        if( typ1.equals(new IntType())){
            if (typ2.equals(new IntType())){
                return new BoolType();
            }else
                throw  new ExpressionException("Second operand is not an integer!");
        }else
            throw  new ExpressionException("First operand is not an integer!");

    }


    @Override
    public String toString() {
        return this.left.toString() + this.operator + this.right.toString();
    }
}

