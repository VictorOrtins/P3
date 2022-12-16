import java.util.Scanner;

public class Main{
    public static void main(String[] args) throws Exception {
        Stack<Character> pilhaParenteses = new Stack<Character>();

        Scanner scan = new Scanner(System.in);

        boolean correct;
        String expression;

        char tempChar;
        char tempChar2;

        /* (a+b*(2-c)-2+a)*2 */

        while(scan.hasNext()){
            correct = true;
            expression = scan.nextLine();

            for(int i = 0; i < expression.length(); i++){
                tempChar = expression.charAt(i);
                if(tempChar == '('){
                    pilhaParenteses.push(tempChar);
                }
                else if(tempChar == ')'){
                    try{
                        tempChar2 = pilhaParenteses.pop();
                    }
                    catch(EmptyListException e){
                        correct = false;
                        break;
                    }

                    // System.out.println(pilhaParenteses.printList());
                }

                if(i == expression.length() - 1){
                    if(pilhaParenteses.getSize() > 0){
                        // System.out.println("teste");
                        correct = false;
                        break;
                    }
                }
            }

            if(correct){
                System.out.println("correct");
            }
            else{
                System.out.println("incorrect");
            }

            pilhaParenteses = new Stack<Character>();
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
