package model.adt;

import exceptions.AdtException;

import java.util.HashMap;

public interface ILockTable {
    void put(Integer key, Integer value) throws AdtException;
    Integer get(Integer key) throws AdtException;
    boolean containsKey(Integer key);
    int getFreeAddress();
    void setFreeAddress(Integer freeAddress);
    void update(Integer key, Integer value) throws AdtException;
    HashMap<Integer, Integer> getLockTable();
}
