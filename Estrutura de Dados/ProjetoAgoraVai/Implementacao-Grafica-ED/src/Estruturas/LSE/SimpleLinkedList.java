package Estruturas.LSE;

import Estruturas.Cores;
import Estruturas.EmptyStructureException;
import Estruturas.SimpleNode;

public class SimpleLinkedList<T>{
    private SimpleNode<T> head;
    private int size;

    private final int MAX_NODOS_LINHA = 6;

    public SimpleLinkedList(){
        head = null;
        size = 0;
    }

    public boolean isEmpty(){
        if (size == 0){
            return true;
        }

        return false;
    }

    public T valueInPosition(int position) throws EmptyStructureException{
        if (!checkValidPosition(position)){
            throw new IllegalArgumentException();
        }
        else if (isEmpty()){
            throw new EmptyStructureException();
        }

        SimpleNode<T> temp = head;
        int count = 1;

        while(count < position){
            temp = temp.getNext();
            count++;
        }

        return temp.getValue();
    }

    public SimpleLinkedList<Integer> positionsOfValue(T value) throws EmptyStructureException{
        if (isEmpty()){
            throw new EmptyStructureException();
        }

        SimpleLinkedList<Integer> list = new SimpleLinkedList<Integer>();

        int list_count = 1;
        SimpleNode<T> temp = head;

        while(temp != null){
            if (temp.getValue().equals(value)){
                list.insertEnd(list_count);
            }

            temp = temp.getNext();
            list_count++;
        }

        return list;
    }

    public boolean insertBeggining(T value){
        SimpleNode<T> newHead = new SimpleNode<T>();
        newHead.setValue(value);
        newHead.setNext(head);

        this.head = newHead;
        sizePlus(1);

        return true;
    }

    public boolean insertEnd(T value){

        SimpleNode<T> newTail = new SimpleNode<T>();
        newTail.setValue(value);

        if (head == null){
            this.head = newTail;
            return true;
        }

        SimpleNode<T> temp = this.head;

        while(temp.getNext() != null){
            temp = temp.getNext();
        }

        newTail.setNext(null);

        temp.setNext(newTail);

        sizePlus(1);

        return true;
    }

    private boolean insertMiddle(T value, int position){
        SimpleNode<T> temp = this.head;
        int cont = 1;

        while(cont < position - 1 && temp != null){ //Revisar pq precisa do temp != null
            temp = temp.getNext();
            cont++;
        }

        if (temp == null){
            return false;
        }

        SimpleNode<T> newMiddle = new SimpleNode<T>();
        newMiddle.setValue(value);

        newMiddle.setNext(temp.getNext());
        temp.setNext(newMiddle);

        sizePlus(1);

        return true;
    }

    public boolean insert(T value, int position){

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

    public boolean remove(int position) throws EmptyStructureException{
        if (!checkValidPosition(position)){
            return false;
        }

        if (isEmpty()){
            throw new EmptyStructureException();
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

    private boolean removeBeggining(){

        SimpleNode<T> temp = this.head.getNext();
        head.setNext(null);

        this.head = temp;
        sizePlus(-1);

        return true;

    }

    private boolean removeEnd(){
        SimpleNode<T> temp = this.head;
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

    private boolean removeMiddle(int position){
        SimpleNode<T> beforePosition;
        SimpleNode<T> afterPosition;

        SimpleNode<T> temp = this.head;
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

    public void clearList(){
        head = null;
        size = 0;
    }

    public SimpleNode<T> getHead() {
        return this.head;
    }

    public void setHead(SimpleNode<T> head) {
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
        SimpleNode<T> temp = this.head;

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

    public String print(boolean pesquisaValor, T valor, boolean pesquisaPosicao, int posicao){
        //Intenção é o limite ser de 10 caracteres
        SimpleNode<T> temp = this.head;
        if(temp == null){
            return "Lista vazia";
        }

        if(pesquisaPosicao && !checkValidPosition(posicao)){
            return "Posição inválida\n";
        }

        String ret = "";

        String linha1 = "";
        String linha2 = "";
        String linha3 = "";
        String linha4 = "";

        String temp_str = "";

        int linha2_length = 0;
        int next_position = 0;
        int contador_nodos = 1;

        while(temp != null){
            temp_str = "| " + temp.getValue().toString() + " |";
            linha2_length = temp_str.length();

            if(pesquisaValor && valor.equals(temp.getValue()) || pesquisaPosicao && posicao == contador_nodos){
                temp_str = "| " + Cores.ANSI_GREEN + temp.getValue().toString() + Cores.ANSI_RESET + " |";
            }
            else{
                temp_str = "| " + temp.getValue().toString() + " |";
            }

            linha2 += temp_str;

            if(contador_nodos % MAX_NODOS_LINHA != 0 && contador_nodos != size){
                temp_str = "  - - -  ";
                linha2 += temp_str;
            }


            for(int i = 0; i < linha2_length; i++){
                linha1 += "-";
                if(contador_nodos % MAX_NODOS_LINHA == 0 && (i == linha2_length/2)){
                    linha3 += "|";
                    next_position = linha3.length();
                }
                else{
                    linha3 += "-";
                }
            }

            if(contador_nodos % MAX_NODOS_LINHA != 0){
                for(int i = 0; i < temp_str.length(); i++){
                    linha1 += " ";
                    linha3 += " ";
                }
            }
            else if(contador_nodos < size){
                for(int i = 0; i < next_position - 1; i++){
                    linha4 += " ";
                }
                linha4 += "|\n";

                for(int i = 0; i < 3; i++){
                    linha4 += " ";
                }

                linha4 += "|";
                for(int i = 0; i < next_position - 3 - 1; i++){
                    linha4 += "-";
                }
            }


            temp = temp.getNext();
            if(contador_nodos % MAX_NODOS_LINHA == 0 || contador_nodos == size){
                ret += linha1 + "\n" + linha2 + "\n" + linha3 + "\n" + linha4 + "\n";
                linha1 = "";
                linha2 = "";
                linha3 = "";
                linha4 = "";
            }
            contador_nodos++;
        }

        return ret;
    }

    public void clear(){
        head = null;
        size = 0;
    }

}