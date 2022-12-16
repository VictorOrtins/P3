package SimpleLinkedList;

import java.util.Objects;

public class SimpleNodeInt {
    private int value;
    private SimpleNodeInt next;

    public SimpleNodeInt(){
        this.value = 0;
        this.next = null;
    }
    public SimpleNodeInt(int value, SimpleNodeInt next){
        this.value = value;
        this.next = next;
    }

    public int getValue() {
        return this.value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public SimpleNodeInt getNext() {
        return this.next;
    }

    public void setNext(SimpleNodeInt next) {
        this.next = next;
    }

    @Override
    public String toString(){
        String ret = "";
        ret += "Value: " + value + "\n";
        ret += "Next: " + next + "\n";

        return ret;
    }




    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof SimpleNodeInt)) {
            return false;
        }
        SimpleNodeInt simpleNodeInt = (SimpleNodeInt) o;
        return value == simpleNodeInt.value && Objects.equals(next, simpleNodeInt.next);
    }

    @Override
    public int hashCode() {
        return Objects.hash(value, next);
    }





}
