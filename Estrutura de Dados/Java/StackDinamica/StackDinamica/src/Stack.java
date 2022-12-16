public class Stack<T> {

    private Node top;
    private int size;

    public Stack(){
        top = null;
        size = 0;
    }

    public boolean isEmpty(){
        if (size == 0){
            return true;
        }

        return false;
    }

    public T getTop(){
        return this.top.value;
    }

    public int getSize() {
        return this.size;
    }

    public boolean push(T value){
        Node aux = new Node();

        aux.setValue(value);
        aux.setNext(top);

        top = aux;

        // System.out.println("Aux = " + aux.getValue());
        // System.out.println("Aux.getNext = " + aux.getNext().getValue());

        sizePlus(1);

        return true;
    }

    public boolean pop(){
        Node aux = top;

        top = aux.getNext();
        aux.setNext(null);

        sizePlus(-1);

        return true;
    }

    public Node getterTop() {
        return this.top;
    }

    public void setTop(Node top) {
        this.top = top;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public void sizePlus(int update){
        this.size += update;
    }

    public String printStack(){
        String ret = "[ ";
        Node aux = top;

        while(aux != null){
            ret += aux.getValue() + " ";
            aux = aux.getNext();
        }

        ret += "]";

        return ret;
    }

    

    class Node{
        private Node next;
        private T value;

        public Node(){
            next = null;
            value = null;
        }

        public Node getNext(){
            return next;
        }

        public T getValue(){
            return value;
        }

        public void setNext(Node next){
            this.next = next;
        }

        public void setValue(T value){
            this.value = value;
        }
    }
}
