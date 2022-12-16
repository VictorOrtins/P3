public class Stack {
    public static final int STACK_MAX_SIZE = 100;
    private Integer stack[];
    private int positionTop;

    public Stack(){
        stack = new Integer[STACK_MAX_SIZE];
        positionTop = 1;
    }

    public boolean isEmpty(){
        if (getSize() == 0){
            return false;
        }

        return true;
    }

    public boolean isFull(){
        if(getSize() == STACK_MAX_SIZE){
            return true;
        }

        return false;
    }

    public int getTop(){
        return stack[positionTop - 2]; //-1 por causa da indexação do array
                                       //E outro -1 pelo positionTop começar com 1
    }

    public boolean push(int value){

        if (isFull()){
            return false;
        }

        stack[positionTop - 1] = value;
        positionTopPlus(1);
        // System.out.println("Position top: " + positionTop);

        return true;
    }

    public boolean pop(){
        // int aux = stack[positionTop - 1];

        stack[positionTop - 1] = null;
        positionTopPlus(-1);
        // System.out.println("Position top: " + positionTop);

        return false;
    }

    public int getSize(){
        return positionTop - 1;
    }

    public Integer[] getStack() {
        return this.stack;
    }

    public void setStack(Integer stack[]) {
        this.stack = stack;
    }

    public int getPositionTop() {
        return this.positionTop;
    }

    public void setPositionTop(int positionTop) {
        this.positionTop = positionTop;
    }

    public void positionTopPlus(int update){
        positionTop += update;
    }

    public String printStack(){
        String ret = "[ ";
        for(int i = 0; i < getSize(); i++){
            ret += stack[i] + " ";
        }

        ret += "]";

        return ret;
    }

}
