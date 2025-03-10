package model.adt;
import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements MyIList<T> {
    List<T> list;
    public MyList(){
        this.list = new ArrayList<T>();
    }

    @Override
    public void add(T elem) {
        this.list.add(elem);
    }
    @Override
    public void remove(T element) {
        list.remove(element);
    }

    @Override
    public List<T> getAll() {
        return this.list;
    }

    @Override
    public String toString() {

        StringBuilder string = new StringBuilder();

        for(T el : this.list){
            string.append(el);
            string.append("\n");
        }

        return "List contains: " + string.toString();

    }
}
