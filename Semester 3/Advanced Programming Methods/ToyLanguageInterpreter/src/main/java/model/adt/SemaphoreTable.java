package model.adt;

import exceptions.AdtException;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.ReentrantLock;

public class SemaphoreTable implements ISemaphoreTable {

    private HashMap<Integer, Pair<Integer, List<Integer>>> semaphoreTable;
    ReentrantLock lock;
    private int freeLocation = 0;

    public SemaphoreTable() {
        this.semaphoreTable = new HashMap<>();
        this.lock = new ReentrantLock();
    }

    @Override
    public void put(int key, Pair<Integer, List<Integer>> value) throws AdtException {
        synchronized (this) {
            if (!semaphoreTable.containsKey(key)) {
                semaphoreTable.put(key, value);
            } else {
                throw new AdtException("Semaphore table already contains the key!");
            }
        }
    }

    @Override
    public Pair<Integer, List<Integer>> get(int key) throws AdtException {
        synchronized (this) {
            if (semaphoreTable.containsKey(key)) {
                return semaphoreTable.get(key);
            } else {
                throw new AdtException(String.format("Semaphore table doesn't contain the key %d!", key));
            }
        }
    }

    @Override
    public boolean containsKey(int key) {
        synchronized (this) {
            return semaphoreTable.containsKey(key);
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
    public void setFreeAddress(int freeAddress) {
        synchronized (this) {
            this.freeLocation = freeAddress;
        }
    }

    @Override
    public void update(int key, Pair<Integer, List<Integer>> value) throws AdtException {
        synchronized (this) {
            if (semaphoreTable.containsKey(key)) {
                semaphoreTable.replace(key, value);
            } else {
                throw new AdtException("Semaphore table doesn't contain key");
            }
        }
    }

    @Override
    public HashMap<Integer, Pair<Integer, List<Integer>>> getSemaphoreTable() {
        synchronized (this) {
            return semaphoreTable;
        }
    }

    @Override
    public void setSemaphoreTable(HashMap<Integer, Pair<Integer, List<Integer>>> newSemaphoreTable) {
        synchronized (this) {
            this.semaphoreTable = newSemaphoreTable;
        }
    }

//    HashMap<Integer, Pair<Integer, List<Integer>>> to list

    public List<Pair<Pair<Integer, Integer>, List<Integer>>> getSemaphoreDictionaryAsList() {
        this.lock.lock();
        List<Pair<Pair<Integer, Integer>, List<Integer> > > answer = new ArrayList<>();
        this.semaphoreTable.forEach((x, y) -> {
            answer.add(new Pair<>(new Pair<>(x, y.getKey()), y.getValue()));
        });
        this.lock.unlock();
        return answer;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("SemaphoreTable:\n");
        for (Map.Entry<Integer, Pair<Integer, List<Integer>>> entry : this.semaphoreTable.entrySet()) {
            Integer key = entry.getKey();
            Pair<Integer, List<Integer>> value = entry.getValue();
            Integer count = value.getKey();
            List<Integer> threads = value.getValue();

            sb.append(String.format("ID: %d -> (Count: %d, Threads: %s)\n", key, count, threads.toString()));
        }
        return sb.toString();
    }
}