package model.type;

import model.value.IValue;
import model.value.RefValue;

public class RefType implements IType{


    private IType inner;

    public RefType(IType inner)
    {
        this.inner = inner;
    }

    public IType getInner()
    {
        return this.inner;
    }
    @Override
    public boolean equals(IType another) {
        return another instanceof RefType && ((RefType) another).getInner().equals(this.inner);
    }

    @Override
    public IValue getDefaultValue() {
        return new RefValue(0,inner);
    }

    @Override
    public String toString()
    {
        return "ref " + this.inner.toString();
    }
}
