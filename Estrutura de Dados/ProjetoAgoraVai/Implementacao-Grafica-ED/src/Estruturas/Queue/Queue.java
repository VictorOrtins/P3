package Estruturas.Queue;

import Estruturas.Cores;
import Estruturas.EmptyStructureException;
import Estruturas.SimpleNode;

public class Queue<Type> {
    private SimpleNode<Type> head;
    private SimpleNode<Type> tail;
    private int size;
    private final int MAX_NODOS_LINHA = 6;

    public Queue(){
        head = null;
        tail = null;
        size = 0;
    }

    public boolean isEmpty(){
        if(size == 0){
            return true;
        }

        return false;
    }

    public Type first(){
        return head.getValue();
    }

    public boolean add(Type value){
        SimpleNode<Type> newNode = new SimpleNode<Type>();

        newNode.setValue(value);
        newNode.setNext(null);

        if(size == 0){
            head = newNode;
        }
        else{
            tail.setNext(newNode);
        }

        tail = newNode;
        size++;

        return true;
    }

    public Type remove() throws EmptyStructureException{

        if(isEmpty()){
            throw new EmptyStructureException();
        }

        SimpleNode<Type> aux = head;

        head = head.getNext();
        size--;

        if(size == 1){
            tail = head;
        }

        aux.setNext(null);

        return aux.getValue();
    }

    public String printQueue(){

        String ret = "[ ";
        SimpleNode<Type> aux = head;

        while(aux != null){
            ret+= aux.getValue() + " ";
            aux = aux.getNext();
        }

        ret += "]";

        return ret;
    }

    public String print(boolean pesquisaValor, Type valor, boolean pesquisaPosicao, int posicao){
        //Intenção é o limite ser de 10 caracteres
        SimpleNode<Type> temp = this.head;
        if(temp == null){
            return "Fila vazia";
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
        tail = null;
        size = 0;
    }

    public SimpleNode<Type> getHead() {
        return this.head;
    }

    public void setHead(SimpleNode<Type> head) {
        this.head = head;
    }

    public SimpleNode<Type> getTail() {
        return this.tail;
    }

    public void setTail(SimpleNode<Type> tail) {
        this.tail = tail;
    }

    public int getSize() {
        return this.size;
    }

    public void setSize(int size) {
        this.size = size;
    }
}
