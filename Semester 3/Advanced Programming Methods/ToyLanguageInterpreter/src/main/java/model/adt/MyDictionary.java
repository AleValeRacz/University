package model.adt;
import exceptions.AdtException;
import exceptions.ExpressionException;

import java.util.*;

public class MyDictionary<K,V> implements MyIDictionary<K,V> {
   Map<K,V> map;

   public MyDictionary(){

       this.map = new HashMap<K,V>();
   }


    public MyDictionary(Map<K, V> map) {
        this.map = map;
    }
    @Override
    public void insert(K key, V value) {

       this.map.put(key,value);
    }

    @Override
    public void remove(K key) throws ExpressionException {
        if(this.map.containsKey(key))
            this.map.remove(key);
        else
            throw new ExpressionException("Dictionary remove: Key not found!\n");
    }

    @Override
    public boolean contains(K key) {
        return this.map.containsKey(key);
    }

    @Override
    public Collection<V> getValues() {
        return this.map.values();
    }

    @Override
    public V get(K key) throws ExpressionException {
       if(this.map.containsKey(key))
        return this.map.get(key);
       else throw new ExpressionException("Dictionary get: Key "+ key+ " not found!\n");
    }

    @Override
    public Set<K> getKeys() {
        return this.map.keySet();
    }

    @Override
    public Map<K, V> getContent() {
        return this.map;
    }



    @Override
    public String toString() {
        StringBuilder st = new StringBuilder();
        this.map.forEach((k,v)->{
            st.append(k).append(" -> ").append(v).append("\n");
        });
        return "Dictionary contains: " + st.toString();

    }

    public MyIDictionary<K, V> deepCopy() {
        Map<K, V> newMap = new HashMap<>();
        for (Map.Entry<K, V> entry : this.map.entrySet()) {
            K deepKey = copyKey(entry.getKey());
            V deepValue = copyValue(entry.getValue());
            newMap.put(deepKey, deepValue);
        }
        return new MyDictionary<>(newMap);
    }

    private K copyKey(K key) {
        return key;
    }

    private V copyValue(V value) {
        return value;
    }

}


