public class Queue<Type> {
    private Node head;
    private Node tail;
    private int size;

    public Queue(){
        head = null;
        tail = null;
        size = 0;
    }

    public boolean isEmpty(){
        if(size == 0){
            return true;
        }

        return false;
    }

    public Type first(){
        return head.getValue();
    }

    public boolean add(Type value){
        Node newNode = new Node();

        newNode.setValue(value);
        newNode.setNext(null);

        if(size == 0){
            head = newNode;
        }
        else{
            tail.setNext(newNode);
        }

        tail = newNode;
        size++;

        return true;
    }

    public Type remove() throws EmptyListException{

        if(isEmpty()){
            throw new EmptyListException();
        }

        Node aux = head;

        head = head.getNext();
        size--;

        if(size == 1){
            tail = head;
        }

        aux.setNext(null);

        return aux.getValue();
    }

    public String printQueue(){

        String ret = "[ ";
        Node aux = head;

        while(aux != null){
            ret+= aux.getValue() + " ";
            aux = aux.getNext();
        }

        ret += "]";

        return ret;
    }

    public Node getHead() {
        return this.head;
    }

    public void setHead(Node head) {
        this.head = head;
    }

    public Node getTail() {
        return this.tail;
    }

    public void setTail(Node tail) {
        this.tail = tail;
    }

    public int getSize() {
        return this.size;
    }

    public void setSize(int size) {
        this.size = size;
    }


    class Node{
        Node next;
        Type value;

        public Node(){
            next = null;
            value = null;
        }

        public void setNext(Node next){
            this.next = next;
        }

        public void setValue(Type value){
            this.value = value;
        }

        public Node getNext(){
            return this.next;
        }

        public Type getValue(){
            return this.value;
        }


    }
}
