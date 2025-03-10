package model.adt;

import exceptions.ExpressionException;
import model.value.IValue;

import java.util.Map;

public interface IHeap {
    public Integer allocate(IValue name);
    public  IValue get(Integer adress) throws ExpressionException;
    public boolean exists(Integer adress);
    public void set(Integer asdress, IValue value);
    public Map<Integer,IValue> getHeap();
    public Integer getFreeLocation();
    public void setHeap(Map<Integer,IValue> new_map);
}
