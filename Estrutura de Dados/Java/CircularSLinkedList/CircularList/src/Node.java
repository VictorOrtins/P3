public class Node<T>{
    private T value;
    private Node<T> next;

    public Node(){
        value = null;
        next = null;
    }

    public T getValue(){
        return this.value;
    }

    public Node<T> getNext(){
        return this.next;
    }

    public void setValue(T value){
        this.value = value;
    }

    public void setNext(Node<T> next){
        this.next = next;
    }
}