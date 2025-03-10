package model.adt;

import exceptions.AdtException;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.ReentrantLock;

public class LockTable implements ILockTable{
    private HashMap<Integer, Integer> latchTable;
    private int freeLocation = 0;

    public LockTable() {
        this.latchTable = new HashMap<>();
    }

    @Override
    public void put(Integer key, Integer value) throws AdtException {
        synchronized (this) {
            if (!latchTable.containsKey(key)) {
                latchTable.put(key, value);
            } else {
                throw new AdtException("Latch table already contains the key!");
            }
        }
    }

    @Override
    public Integer get(Integer key) throws AdtException {
        synchronized (this) {
            if (latchTable.containsKey(key)) {
                return latchTable.get(key);
            } else {
                throw new AdtException(String.format("Latch table doesn't contain the key %d!", key));
            }
        }
    }

    @Override
    public boolean containsKey(Integer key) {
        synchronized (this) {
            return latchTable.containsKey(key);
        }
    }

    @Override
    public int getFreeAddress() {
        synchronized (this) {
            freeLocation++;
            return freeLocation;
        }
    }

    @Override
    public void setFreeAddress(Integer freeAddress) {
        synchronized (this) {
            this.freeLocation = freeAddress;
        }
    }

    @Override
    public void update(Integer key, Integer value) throws AdtException {
        synchronized (this) {
            if (latchTable.containsKey(key)) {
                latchTable.replace(key, value);
            } else {
                throw new AdtException("Semaphore table doesn't contain key");
            }
        }
    }

    @Override
    public HashMap<Integer, Integer> getLockTable() {
        synchronized (this) {
            return latchTable;
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("lockTable:\n");
        for (Map.Entry<Integer,Integer> entry : this.latchTable.entrySet()) {
            Integer key = entry.getKey();
            Integer value = entry.getValue();
            sb.append("location: ").append(key).append("->value: ").append(value);
        }
        return sb.toString();
    }
}
