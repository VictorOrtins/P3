public class CircularList<T>{

    private Node<T> cursor;
    private int size;

    public CircularList(){
        cursor = null;
        size = 0;
    }

    public Node<T> getCursor(){
        return cursor;
    }

    public int getSize(){
        return size;
    }

    public boolean add(T value){
        Node<T> newNode = new Node<T>();
        newNode.setValue(value);

        if(size == 0){
            cursor = newNode;
            cursor.setNext(newNode);
            sizePlus(1);
            return true;
        }

        newNode.setNext(cursor.getNext());
        cursor.setNext(newNode);

        sizePlus(1);

        return true;
    }

    public boolean remove(){
        if(size == 1){
            cursor = null;
            sizePlus(-1);
            return true;
        }
        else if(size == 0){
            return false;
        }

        Node<T> removedNode = cursor.getNext();

        cursor.setNext(removedNode.getNext());
        removedNode.setNext(null);
        
        sizePlus(-1);

        return true;
    }

    public void advance(){
        cursor = cursor.getNext();
    }

    public String printList(){
        if(cursor == null){
            return "[ ]";
        }

        String ret = "[ " + cursor.getValue() + " ";
        Node<T> oldCursor = cursor;
        for(advance(); oldCursor != cursor; advance()){
            ret += cursor.getValue() + " ";
        }

        ret += "]";
        return ret;
    }

    private void sizePlus(int update){
        size += update;
    }

    public void setCursor(Node<T> cursor){
        this.cursor = cursor;
    }
}