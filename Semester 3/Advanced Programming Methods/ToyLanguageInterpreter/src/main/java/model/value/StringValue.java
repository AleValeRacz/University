package model.value;

import model.type.IType;
import model.type.StringType;

public class StringValue implements IValue{
   public String value;

   public StringValue(String value){
       this.value = value;
   }

   public String getValue(){
       return this.value;
   }
    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public boolean equals(IValue value) {
        return value instanceof  StringValue &&((StringValue)value).value.equals(this.value);
    }

    @Override
    public IValue deepCopy() {
        return new StringValue(this.value);
    }
    @Override
    public String toString()
    {
        return this.value;
    }
}
