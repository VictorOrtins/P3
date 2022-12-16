import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
        Stack<Integer> pilhaPapaiNoel = new Stack<Integer>();
        Stack<Integer> filaAuxiliar = new Stack<Integer>();
        
        String input[] = new String[2];
        try (Scanner scan = new Scanner(System.in)) {
            int numOperations = scan.nextInt();
            int push_num, min = 0, teste;
            for(int i = 0; i <= numOperations; i++){
                input = scan.nextLine().split(" ");
                switch(input[0]){
                    case "PUSH":{
                        push_num = Integer.parseInt(input[1]);
                        pilhaPapaiNoel.push(push_num);
                        // System.out.println(pilhaPapaiNoel.printList());
                        // System.out.println(pilhaPapaiNoel.getSize());
                        break;
                    }
                    case "MIN":{
                        if(pilhaPapaiNoel.getSize() == 0){
                            System.out.println("EMPTY");
                            break;
                        }
                        
                        for(int j = 0; j <= pilhaPapaiNoel.getSize(); j++){
                            if(j == 0){
                                min = pilhaPapaiNoel.pop();
                                // System.out.println(min + " opa 1");
                                filaAuxiliar.push(min);
                            }
                            else{
                                teste = pilhaPapaiNoel.pop();
                                // System.out.println(teste + " opa 2");
                                filaAuxiliar.push(teste);
                                if(teste < min){
                                    min = teste;
                                }
                            }
                        }

                        System.out.println(min);
                        if(filaAuxiliar.getSize() > 1){
                            for(int j = 0; j <= filaAuxiliar.getSize() + 1; j++){
                                teste = filaAuxiliar.pop();
                                pilhaPapaiNoel.push(teste);
                            }
                        }

                        // System.out.println(pilhaPapaiNoel.printList());
                        // System.out.println(pilhaPapaiNoel.getSize());
                        break;
                    }
                    case "POP":{
                        if(pilhaPapaiNoel.getSize() == 0){
                            System.out.println("EMPTY");
                            break;
                        }
                        
                        pilhaPapaiNoel.pop();
                        // System.out.println(pilhaPapaiNoel.printList());
                        // System.out.println(pilhaPapaiNoel.getSize());
                        break;
                    }
                }
            }
        }
    }    
}

class EmptyListException extends Exception{
    
}

class Queue<T>{

    private Node header;
    private Node trailer;
    private int size;

    public Queue() {
        this.header = null;
        this.trailer = null;
        this.size = 0;
    }

    public boolean isEmpty(){
        if(size == 0){
            return true;
        }

        return false;
    }

    public boolean add(T value){
        Node newNode = new Node();
        newNode.setValue(value);

        if(isEmpty()){
            header = newNode;
        }else{
            trailer.setNext(newNode);
        }

        trailer = newNode;
        size++;

        return true;
    }

    public T remove() throws EmptyListException{
        if(isEmpty()){
            throw new EmptyListException();
        }

        Node aux = header;
        header = aux.getNext();

        aux.setNext(null);
        size--;

        if(getSize() == 1){
            trailer = header;
        }

        return aux.getValue();
    }

    public String printList(){
        String ret = "[ ";

        Node aux = header;
        while(aux != null){
            ret += aux.getValue() + " ";
            aux = aux.getNext();
        }

        ret += "]";

        return ret;
    }

    public Node getHeader() {
        return this.header;
    }

    public void setHeader(Node header) {
        this.header = header;
    }

    public Node getTrailer() {
        return this.trailer;
    }

    public void setTrailer(Node trailer) {
        this.trailer = trailer;
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

        public void setValue(T value){
            this.value = value;
        }

        public void setNext(Node next){
            this.next = next;
        }

        public T getValue(){
            return value;
        }

        public Node getNext(){
            return next;
        }
    }
}

class Stack<T>{

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
            // System.out.println(this.getSize());
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
