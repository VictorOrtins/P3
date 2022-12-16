import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws Exception {
        Scanner scan = new Scanner(System.in);
        Queue<Pessoa> fila = new Queue<Pessoa>();

        // String inputString[];
        int inputs[] = new int[3];

        int numeroPacientes;
        Pessoa temp_paciente;

        int hora = 7, minuto = 0;
        int numCondicaoCritica = 0;

        int horaCondicaoCritica, minutoCondicaoCritica;
        while(scan.hasNextLine()){
            numeroPacientes = scan.nextInt();

            hora = 7; minuto = 0; numCondicaoCritica = 0;
            horaCondicaoCritica = 0; minutoCondicaoCritica = 0;
    
            for(int i = 0; i < numeroPacientes; i++){
                inputs[0] = scan.nextInt();
                inputs[1] = scan.nextInt();
                inputs[2] = scan.nextInt();
    
                for(int j = 0; j < 3; j++){
                }
    
                temp_paciente = new Pessoa(inputs[0], inputs[1], inputs[2]);
                fila.add(temp_paciente);
            }
            int contador = 0;
            while(contador < numeroPacientes){
                try{
                    temp_paciente = fila.remove();
                }
                catch(Exception e){
                    continue;
                }

                if(hora == 7 && minuto == 0 && temp_paciente.getHora() == hora && temp_paciente.getMinuto() == minuto){
                    minuto += 30;
                    continue;
                }
                else{
                    horaCondicaoCritica = temp_paciente.getHora();
                    minutoCondicaoCritica = temp_paciente.getMinuto() + temp_paciente.getMinutosDeSobrevivencia();
                    if(minutoCondicaoCritica >= 60){
                        minutoCondicaoCritica -= 60;
                        horaCondicaoCritica++;
                    }
    
    
                    if(!(horaCondicaoCritica > hora)){
                        if(horaCondicaoCritica == hora && !(minutoCondicaoCritica > minuto)){
                            numCondicaoCritica++;
                        }
                    }
    
                    // System.out.println("Hora de chegada: " + temp_paciente.getHora() + " " + temp_paciente.getMinuto());
                    // System.out.println("Hora de condição crítica: " + horaCondicaoCritica + " " + minutoCondicaoCritica);
                    // System.out.println("Hora atual: " + hora + " " + minuto);
    
                    if(!(temp_paciente.getHora() > hora)){
                        if(temp_paciente.getHora() == hora && !(temp_paciente.getMinuto() > minuto)){
                            // System.out.println("if paciente chegar dps de 30 minutos de consulta");
                            hora = temp_paciente.getHora();
                            minuto = temp_paciente.getMinuto();
                        }
                    }
    
                    minuto += 30;
                    if(minuto >= 60){
                        minuto -= 60;
                        hora++;
                    }
                }
            }
            System.out.println(numCondicaoCritica);
        }
        scan.close();
    }
}

class Pessoa{
    private int hora;
    private int minuto;
    private int minutosDeSobrevivencia;

    public Pessoa(){
        hora = 0;
        minuto = 0;
        minutosDeSobrevivencia = 0;
    }

    public Pessoa(int hora, int minuto, int minutosDeSobrevivencia){
        this.hora = hora;
        this.minuto = minuto;
        this.minutosDeSobrevivencia = minutosDeSobrevivencia;
    }

    public void setHora(int hora){
        this.hora = hora;
    }

    public void setMinuto(int minuto){
        this.minuto = minuto;
    }

    public void setMinutosDeSobrevivencia(int minutosDeSobrevivencia){
        this.minutosDeSobrevivencia = minutosDeSobrevivencia;
    }

    public int getHora(){
        return hora;
    }

    public int getMinuto(){
        return minuto;
    }

    public int getMinutosDeSobrevivencia(){
        return minutosDeSobrevivencia;
    }
}

class EmptyListException extends Exception{
    
}

class Queue<T>{

    private Node header;
    private Node trailer;
    private int size;

    public Queue() {
        this.header = null;
        this.trailer = null;
        this.size = 0;
    }

    public boolean isEmpty(){
        if(size == 0){
            return true;
        }

        return false;
    }

    public boolean add(T value){
        Node newNode = new Node();
        newNode.setValue(value);

        if(isEmpty()){
            header = newNode;
        }else{
            trailer.setNext(newNode);
        }

        trailer = newNode;
        size++;

        return true;
    }

    public T remove() throws EmptyListException{
        if(isEmpty()){
            throw new EmptyListException();
        }

        Node aux = header;
        header = aux.getNext();

        aux.setNext(null);
        size--;

        if(getSize() == 1){
            trailer = header;
        }

        return aux.getValue();
    }

    public String printList(){
        String ret = "[ ";

        Node aux = header;
        while(aux != null){
            ret += aux.getValue() + " ";
            aux = aux.getNext();
        }

        ret += "]";

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

    class Node{
        private T value;
        private Node next;

        public Node(){
            value = null;
            next = null;
        }

        public void setValue(T value){
            this.value = value;
        }

        public void setNext(Node next){
            this.next = next;
        }

        public T getValue(){
            return value;
        }

        public Node getNext(){
            return next;
        }
    }
}
