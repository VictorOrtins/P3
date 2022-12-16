public class DoubleLinkedList<T>{

    private Node header;
    private Node trailer;
    private int size;

    public DoubleLinkedList(){
        header = null;
        trailer = null;
        size = 0;
    }

    public boolean isEmpty(){
        if (size == 0){
            return true;
        }

        return false;
    }

    public T valueInPosition(int position) throws EmptyListException, InvalidPosition{

        if (isEmpty()){
            throw new EmptyListException();
        }

        if (!checkIfValidPosition(position)){
            throw new InvalidPosition();
        }

        Node aux;

        if(size/2 > position){
            aux = header;
            for(int i = 1; i < position; i++){
                aux = aux.getSucessor();
            }

            return aux.getValue();
        }
        else{
            aux = trailer;
            for(int i = size; i > position; i--){ //8 7
                aux = aux.getPredecessor(); //aux = 7; 6;
            }

            return aux.getValue();
        }
        
    }

    public boolean setValueInPosition(T value, int position){
        if (isEmpty()){
            return false;
        }

        if (!checkIfValidPosition(position)){
            return false;
        }

        Node aux;

        if(size/2 > position){
            aux = header;
            for(int i = 1; i < position; i++){
                aux = aux.getSucessor();
            }

            aux.setValue(value);
            return true;

        }
        else{
            aux = trailer;
            for(int i = size; i > position; i--){ //8 7
                aux = aux.getPredecessor(); //aux = 7; 6;
            }
            
            aux.setValue(value);
            return true;
        }
    }

    public DoubleLinkedList<Integer> positionsOfValue(T value){
        Node aux = header;
        DoubleLinkedList<Integer> ret_list = new DoubleLinkedList<Integer>();

        for(int i = 1; i <= size && aux != null; i++){
            if(aux.getValue().equals(value)){
                ret_list.pushBack(i);
            }
            aux = aux.getSucessor();
        }

        return ret_list;
    }

    public int positionOfValue(T value) throws NotFoundException{
        Node aux = header;
        for(int i = 1; i <= size && aux != null; i++){
            if(aux.getValue().equals(value)){
                return i;
            }

            aux = aux.getSucessor();
        }

        throw new NotFoundException();
    }

    public boolean pushFront(T value){
        Node newNode = new Node();
        newNode.setValue(value);

        newNode.setPredecessor(null);

        if(isEmpty()){
            newNode.setSucessor(null);
            trailer = newNode;
        }
        else{
            newNode.setSucessor(header);
            header.setPredecessor(newNode);
        }

        header = newNode;
        sizePlus(1);

        return true;
    }

    public boolean pushBack(T value){
        Node newNode = new Node();
        newNode.setValue(value);

        newNode.setSucessor(null);

        if(isEmpty()){
            newNode.setPredecessor(null);
            header = newNode;
        }
        else{
            newNode.setPredecessor(trailer);
            trailer.setSucessor(newNode);
        }

        trailer = newNode;
        sizePlus(1);

        return true;
    }

    public boolean add(T value, int position){
        // System.out.println("Value: " + value + "\nPosition: " + position);
        if(isEmpty() && position != 1){
            // System.out.println("Empty and position != 1");
            return false;
        }

        if(position > size + 1){
            // System.out.println("position > size + 1");
            return false;
        }


        if(position == 1){
            // System.out.println("Position == 1");
            return pushFront(value);
        }
        else if (position == size + 1){
            // System.out.println("Position == size + 1");
            return pushBack(value);
        }
        else{
            // System.out.println("Else");
            return addPosition(value, position);
        }
        
    }

    private boolean addPosition(T value, int position){

        Node newNode = new Node();
        newNode.setValue(value);
        Node aux;
        
        if(size/2 > position){
            // System.out.println("size/2 > position");
            aux = header;

            for(int i = 1; i < position - 1; i++){ 
                aux = aux.getSucessor(); 
            }
    
            newNode.setPredecessor(aux);
            newNode.setSucessor(aux.getSucessor());
    
            aux.setSucessor(newNode);
            newNode.getSucessor().setPredecessor(newNode);
            sizePlus(1);

            return true;
        }
        else{
            System.out.println("size/2 <= position");
            System.out.println("Position: " + position);
            aux = trailer;
            for(int i = size; i > position; i--){
                aux = aux.getPredecessor();
            }

            System.out.println("Aux: " + aux.getValue());

            newNode.setPredecessor(aux.getPredecessor());
            newNode.setSucessor(aux);

            aux.getPredecessor().setSucessor(newNode);
            aux.setPredecessor(newNode);


            sizePlus(1);

            return true;
        }
    }

    public T unpushFront(){
        Node aux = header;

        Node newHead = aux.getSucessor();

        header = null;
        aux.setSucessor(null);
        newHead.setPredecessor(null);

        header = newHead;

        sizePlus(-1);

        return aux.getValue();
    }

    public T unpushBack(){
        Node aux = trailer;
        Node newTrailer = aux.getPredecessor();

        trailer = null;
        newTrailer.setSucessor(null);
        aux.setPredecessor(null);

        trailer = newTrailer;

        sizePlus(-1);

        return aux.getValue();
    }

    private T removePosition(int position){
        Node aux;

        if(size/2 > position){
            aux = header;
            for(int i = 1; i < position; i++){//1 2
                aux = aux.getSucessor();//2 3
            }
        }
        else{
            aux = trailer;

            for(int i = size; i > position; i--){//8 7
                aux = aux.getPredecessor();//7 6
            }
        }

        aux.getPredecessor().setSucessor(aux.getSucessor());
        aux.getSucessor().setPredecessor(aux.getPredecessor());

        aux.setSucessor(null);
        aux.setPredecessor(null);
        
        sizePlus(-1);
        return aux.getValue();
    }

    public T remove(int position) throws EmptyListException, InvalidPosition{
        if(isEmpty()){
            throw new EmptyListException();
        }

        if(!checkIfValidPosition(position)){
            throw new InvalidPosition();
        }

        if(position == 1){
            return unpushFront();
        }
        else if (position == size){
            return unpushBack();
        }
        else{
            return removePosition(position);
        }
    }



    public String printList(){
        String ret = "[ ";
        Node aux = header;
        while(aux != null){
            ret += aux.getValue() + " ";
            aux = aux.getSucessor();
        }

        ret+= "]";

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

    private boolean checkIfValidPosition(int position){
        return position > 0 && position <= size;
    }

    private void sizePlus(int value){
        size += value;
    }

    class Node{
        private T value;
        private Node sucessor;
        private Node predecessor;

        public T getValue() {
            return this.value;
        }

        public void setValue(T value) {
            this.value = value;
        }

        public Node getSucessor() {
            return this.sucessor;
        }

        public void setSucessor(Node sucessor) {
            this.sucessor = sucessor;
        }

        public Node getPredecessor() {
            return this.predecessor;
        }

        public void setPredecessor(Node predecessor) {
            this.predecessor = predecessor;
        }

        @Override
        public String toString() {
            return
                " Value = " + getValue() + "\n" +
                " Sucessor = " + getSucessor() + "\n" +
                " Predecessor = " + getPredecessor().toString() + "\n";
        }
    }
}
