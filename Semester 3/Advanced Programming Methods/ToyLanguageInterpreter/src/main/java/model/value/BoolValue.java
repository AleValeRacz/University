package model.value;

import model.type.BoolType;
import model.type.IType;

public class BoolValue implements IValue{
    private boolean value;
    public BoolValue(boolean value) {
        this.value = value;
    }
    public boolean getValue() {
        return value;
    }
    public IType getType(){
        return new BoolType();
    }

    public boolean equals(IValue other){
        return other.getType() instanceof BoolType && ((BoolValue)other).getValue() == getValue();
    }

    @Override
    public IValue deepCopy() {
        return new BoolValue(this.value);
    }
    @Override
    public String toString(){
        return Boolean.toString(value);
    }
}
