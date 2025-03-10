package model.adt;

import exceptions.ExpressionException;
import model.value.IValue;

import java.util.HashMap;
import java.util.Map;

public class Heap implements  IHeap{

    private Map<Integer,IValue> map;
    private Integer freeLocation;


    public Heap()
    {
        this.map = new HashMap<>();
        this.freeLocation = 1;
    }

    @Override
    public Integer allocate(IValue name) {
        map.put(freeLocation++, name);
        return freeLocation-1;
    }

    @Override
    public IValue get(Integer address) throws ExpressionException {
        return map.get(address);
    }

    @Override
    public boolean exists(Integer address) {
        return map.containsKey(address);
    }

    @Override
    public void set(Integer address, IValue value) {
        map.put(address,value);
    }


    @Override
    public Map<Integer,IValue> getHeap() {
        return this.map;
    }

    @Override
    public Integer getFreeLocation() {
        return this.freeLocation;
    }

    @Override
    public void setHeap(Map<Integer,IValue> new_map) {
        this.map = new_map;
    }


    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("Heap: \n");
        map.keySet().forEach(key->{

                builder.append(key.toString()+"->"+ map.get(key).toString());


                builder.append("\n");
            }
                );
        return builder.toString();
    }
}
