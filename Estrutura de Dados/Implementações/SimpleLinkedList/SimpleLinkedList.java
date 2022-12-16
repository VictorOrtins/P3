package SimpleLinkedList;


public class SimpleLinkedList {
    private SimpleNodeInt head;
    private int size;

    public SimpleLinkedList(){
        head = null;
        size = 0;
    }

    public boolean isEmpty() /*throws IllegalSizeException*/{
        if (size == 0){
            return true;
        }
        // else if (size < 0){
        //     throw new IllegalSizeException();
        // }

        return false;
    }

    public int valueInPosition(int position) throws EmptyListException{
        if (!checkValidPosition(position)){
            throw new IllegalArgumentException();
        }
        else if (isEmpty()){
            throw new EmptyListException();
        }

        SimpleNodeInt temp = head;
        int count = 1;
        //temp != null seria desnecessário vistoa  checagem de posição válida no início.

        while(/*temp != null &&*/ count < position){
            temp = temp.getNext();
            count++;
        }

        return temp.getValue();
    }

    public SimpleLinkedList positionsOfValue(int value) throws EmptyListException{
        if (isEmpty()){
            throw new EmptyListException();
        }

        SimpleLinkedList list = new SimpleLinkedList();

        int list_count = 1;
        SimpleNodeInt temp = head;

        while(temp != null){
            if (temp.getValue() == value){
                list.insertEnd(list_count);
            }

            temp = temp.getNext();
            list_count++;
        }

        return list;
    }

    public boolean insertBeggining(int value){
        SimpleNodeInt newHead = new SimpleNodeInt();
        newHead.setValue(value);
        newHead.setNext(head);

        this.head = newHead;
        sizePlus(1);

        return true;
    }

    public boolean insertEnd(int value){

        SimpleNodeInt newTail = new SimpleNodeInt();
        newTail.setValue(value);

        if (head == null){
            this.head = newTail;
            return true;
        }

        SimpleNodeInt temp = this.head;

        while(temp.getNext() != null){
            temp = temp.getNext();
        }

        newTail.setNext(null);

        temp.setNext(newTail);

        sizePlus(1);

        return true;
    }

    private boolean insertMiddle(int value, int position){
        SimpleNodeInt temp = this.head;
        int cont = 1;

        while(cont < position - 1 && temp != null){ //Revisar pq precisa do temp != null
            temp = temp.getNext();
            cont++;
        }

        if (temp == null){
            return false;
        }

        SimpleNodeInt newMiddle = new SimpleNodeInt();
        newMiddle.setValue(value);

        newMiddle.setNext(temp.getNext());
        temp.setNext(newMiddle);

        sizePlus(1);

        return true;
    }

    public boolean insert(int value, int position){

        if (position < 1 || position > getSize() + 1){
            return false;
        }

        if (position == 1){
            return insertBeggining(value);
        }
        else if (position == getSize() + 1){
            return insertEnd(value);
        }
        else{
            return insertMiddle(value, position);
        }
    }

    public boolean remove(int position) throws EmptyListException{
        if (!checkValidPosition(position)){
            return false;
        }

        if (isEmpty()){
            throw new EmptyListException();
        }

        if (position == 1){
            return removeBeggining();
        }
        else if (position == size){
            return removeEnd();
        }
        else{
            return removeMiddle(position);
        }
    }

    public boolean removeBeggining(){

        SimpleNodeInt temp = this.head.getNext();
        head.setNext(null);

        this.head = temp;
        sizePlus(-1);

        return true;

    }

    public boolean removeEnd(){
        SimpleNodeInt temp = this.head;
        for (int i = 1; i < size - 1; i++){
            temp = temp.getNext();
        }

        if (temp == null){
            return false;
        }

        temp.setNext(null);

        sizePlus(-1);

        return true;

    }

    public boolean removeMiddle(int position){
        SimpleNodeInt beforePosition;
        SimpleNodeInt afterPosition;

        SimpleNodeInt temp = this.head;
        for (int i = 1; i < position - 1; i++){
            temp = temp.getNext();
        }

        if (temp == null){
            return false;
        }

        beforePosition = temp;
        temp = temp.getNext();
        afterPosition = temp.getNext();

        temp.setNext(null);
        beforePosition.setNext(afterPosition);

        sizePlus(-1);

        return true;
    }

    public SimpleNodeInt getHead() {
        return this.head;
    }

    public void setHead(SimpleNodeInt head) {
        this.head = head;
    }

    public int getSize() {
        return this.size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public void sizePlus(int update){
        size += update;
    }

    public boolean checkValidPosition(int position){
        return position > 0 && position <= size;
    }

    public String printList(){
        String ret = "[";
        SimpleNodeInt temp = this.head;

        while(temp != null){
            ret += temp.getValue();
            if (temp.getNext() != null){
                ret += ", ";
            }
            temp = temp.getNext();
        }

        ret += "]";

        return ret;
    }

}