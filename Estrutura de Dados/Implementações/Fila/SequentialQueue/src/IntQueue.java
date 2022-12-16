public class IntQueue{
    private int array[];
    private int begin;
    private int end;
    private int size;

    public IntQueue(){
        begin = 0;
        end = 0;
        size = 0;

        array = new int[100];
    }

    public IntQueue(int limit){
        begin = 0;
        end = 0;
        size = 0;

        array = new int[limit];
    }

    public boolean isFull(){
        if(size == array.length){
            return true;
        }

        return false;
    }

    public boolean isEmpty(){
        if(size == 0){
            return true;
        }

        return false;
    }

    public int first(){
        return array[begin];
    }

    public boolean add(int value){
        if(isFull()){
            return false;
        }

        if(size != 0){
            end = (end + 1) % array.length;
        }

        array[end] = value;
        size++;
        return true;
    }

    public int remove() throws EmptyListException{
        if(isEmpty()){
            throw new EmptyListException(); 
        }
        int temp = array[begin];

        begin = (begin + 1) % array.length;
        size--;

        return temp;
    }

    public String printQueue(){
        String ret = "[ ";
        int temp = begin;

        while(temp != end){
            ret += array[temp] + " ";
            temp = (temp + 1) % array.length;
        }

        ret += array[temp] + " ";

        ret += "]";

        return ret;
    }


    public int[] getArray() {
        return this.array;
    }

    public void setArray(int array[]) {
        this.array = array;
    }

    public int getBegin() {
        return this.begin;
    }

    public void setBegin(int begin) {
        this.begin = begin;
    }

    public int getEnd() {
        return this.end;
    }

    public void setEnd(int end) {
        this.end = end;
    }

    public int getSize() {
        return this.size;
    }

    public void setSize(int size) {
        this.size = size;
    }



}