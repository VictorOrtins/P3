public class Stack<T>{

    private Node head;
    private int size;

    public Stack(){
        head = null;
        size = 0;
    }

    public boolean isEmpty(){
        if(size == 0){
            return true;
        }

        return false;
    }

    public boolean push(T value){
        Node newHead = new Node();
        newHead.setValue(value);

        if(isEmpty()){
            newHead.setNext(null);
        }
        else{
            newHead.setNext(head);
        }

        head = newHead;
        size++;
        return true;
    }

    public T pop() throws EmptyListException{

        if(isEmpty()){
            throw new EmptyListException();
        }

        Node newHead = head.getNext();
        Node formerHead = head;

        head.setNext(null);
        head = newHead;

        size--;

        return formerHead.getValue();
    }

    public String printList(){
        String ret = "[ ";
        Node aux = head;
        while(aux != null){
            ret += aux.getValue() + " ";
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

    public int getSize() {
        return this.size;
    }

    public void setSize(int size) {
        this.size = size;
    }


    class Node{
        private T value;
        private Node next;
        
        public Node(){
            value = null;
            next = null;
        }

        public T getValue(){
            return value;
        }

        public Node getNext(){
            return next;
        }

        public void setValue(T value){
            this.value = value;
        }

        public void setNext(Node next){
            this.next = next;
        }
    }
}