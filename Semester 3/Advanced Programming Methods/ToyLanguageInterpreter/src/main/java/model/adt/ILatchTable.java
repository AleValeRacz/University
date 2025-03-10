package model.adt;

import exceptions.AdtException;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;

public interface ILatchTable {
    void put(Integer key, Integer value) throws AdtException;
    Integer get(Integer key) throws AdtException;
    boolean containsKey(Integer key);
    int getFreeAddress();
    void setFreeAddress(Integer freeAddress);
    void update(Integer key, Integer value) throws AdtException;
    HashMap<Integer, Integer> getLatchTable();
    //List<Pair<Pair<Integer, Integer>, List<Integer>>> getSemaphoreDictionaryAsList();
    //void setSemaphoreTable(HashMap<Integer, Pair<Integer, List<Integer>>> newSemaphoreTable);

}
