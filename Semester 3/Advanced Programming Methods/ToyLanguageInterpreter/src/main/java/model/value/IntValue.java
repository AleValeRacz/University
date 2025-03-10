package model.value;

import model.type.IType;
import model.type.IntType;

import java.lang.reflect.Type;

public class IntValue implements IValue{
    private int number;
    public IntValue(int number) {
        this.number = number;
    }
    public int getValue() {
        return number;
    }
    public IType getType(){
        return new IntType();
    }

    @Override
    public boolean equals(IValue obj) {
        return obj.getType() instanceof IntType &&((IntValue)obj).getValue()==this.getValue();
    }

    @Override
    public IValue deepCopy() {
        return new IntValue(this.number);
    }

    @Override
    public String toString(){
        return Integer.toString(number);
    }
}
