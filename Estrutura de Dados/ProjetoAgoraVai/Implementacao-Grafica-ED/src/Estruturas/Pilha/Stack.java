package Estruturas.Pilha;

import Estruturas.Cores;
import Estruturas.EmptyStructureException;
import Estruturas.SimpleNode;

public class Stack<T> {

    private SimpleNode<T> top;
    private int size;

    public Stack(){
        top = null;
        size = 0;
    }

    public boolean isEmpty(){
        if (size == 0){
            return true;
        }

        return false;
    }

    public T getTop(){
        return this.top.getValue();
    }

    public int getSize() {
        return this.size;
    }

    public boolean push(T value){
        SimpleNode<T> aux = new SimpleNode<T>();

        aux.setValue(value);
        aux.setNext(top);

        top = aux;

        // System.out.println("Aux = " + aux.getValue());
        // System.out.println("Aux.getNext = " + aux.getNext().getValue());

        sizePlus(1);

        return true;
    }

    public boolean pop() throws EmptyStructureException{

        if(isEmpty()){
            throw new EmptyStructureException();
        }
        
        SimpleNode<T> aux = top;

        top = aux.getNext();
        aux.setNext(null);

        sizePlus(-1);

        return true;
    }

    public SimpleNode<T> getterTop() {
        return this.top;
    }

    public void setTop(SimpleNode<T> top) {
        this.top = top;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public void sizePlus(int update){
        this.size += update;
    }

    public void clear(){
        top = null;
        size = 0;
    }

    public String printStack(){
        String ret = "[ ";
        SimpleNode<T> aux = top;

        while(aux != null){
            ret += aux.getValue() + " ";
            aux = aux.getNext();
        }

        ret += "]";

        return ret;
    }

    public String print(boolean pesquisaValor, T valor, boolean pesquisaPosicao, int posicao){
        SimpleNode<T> temp = top;
        
        if(temp == null){
            return "Pilha vazia";
        }

        String ret = "";

        String linha1 = "";
        String linha2 = "";
        String linha3 = "";
        String linha4 = "";

        String temp_str = "";

        int linha2_length = 0;
        int contador_nodos = 1;

        final int CENTRO = 70;
        final int TRACOS = 11;
        

        while(temp != null){

            for(int i = 0; i < CENTRO/2; i++){
                linha1 += " ";
                linha2 += " ";
                linha3 += " ";
                linha4 += " ";
            }

            temp_str = "| " + temp.getValue().toString() + " |";
            linha2_length = temp_str.length();

            if(pesquisaValor && valor.equals(temp.getValue()) || pesquisaPosicao && posicao == contador_nodos){
                temp_str = "| " + Cores.ANSI_GREEN + temp.getValue().toString() + Cores.ANSI_RESET + " |";
            }
            else{
                temp_str = "| " + temp.getValue().toString() + " |";
            }

            temp_str = removeSuffix(temp_str, "|");
            for(int i = 0; i < TRACOS - linha2_length; i++){
                temp_str += " ";
            }
            temp_str += " |";
            linha2 += temp_str;

            if(contador_nodos != size){
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < TRACOS/2; j++){
                        linha4 += " ";
                    }

                    linha4 += "|";
                    if(i != 2){
                        linha4 += "\n";
                    }

                    for(int j = 0; j < CENTRO/2; j++){
                        linha4 += " ";
                    }
                }
            }


            for(int i = 0; i < 11; i++){
                linha1 += "-";
                linha3 += "-";
            }

            // if(contador_nodos % MAX_NODOS_LINHA != 0){
            //     for(int i = 0; i < temp_str.length(); i++){
            //         linha1 += " ";
            //         linha3 += " ";
            //     }
            // }
            // else if(contador_nodos < size){
            //     linha4 += "|";
            //     for(int i = 0; i < next_position; i++){
            //         linha4 += "-";
            //     }
            // }


            temp = temp.getNext();
            ret += linha1 + "\n" + linha2 + "\n" + linha3 + "\n" + linha4 + "\n";
            linha1 = "";
            linha2 = "";
            linha3 = "";
            linha4 = "";
            
            contador_nodos++;
        }

        return ret;
    }

    public static String removeSuffix(final String s, final String suffix)
    {
        if (s != null && suffix != null && s.endsWith(suffix)) {
            return s.substring(0, s.length() - suffix.length());
        }
        return s;
    }
}
