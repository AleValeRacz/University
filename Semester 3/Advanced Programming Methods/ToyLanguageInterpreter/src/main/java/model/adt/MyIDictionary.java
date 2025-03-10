package model.adt;

import exceptions.ExpressionException;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

public interface MyIDictionary<K,V> {
    void insert(K key, V value);
    void remove(K key) throws ExpressionException;
    public boolean contains(K key);
    public Collection<V> getValues();
    public V get(K key) throws ExpressionException;
    public Set<K> getKeys();
    public MyIDictionary<K,V> deepCopy();
    public Map<K, V> getContent();


}
