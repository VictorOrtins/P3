import java.util.Scanner;


public class App{
    public static void main(String[] args) throws EmptyListException, InvalidPosition {
        Scanner scan = new Scanner(System.in);

        DoubleLinkedList<Integer> lista;
        DoubleLinkedList<Integer> retirados;

        final int INPUTS = 3;

        String str_input[] = scan.nextLine().split(" ");
        int input[] = new int[INPUTS];

        for(int i = 0; i < INPUTS; i++){
            input[i] = Integer.parseInt(str_input[i]);
        }

        int saltoHorario;
        int saltoAntiHorario;
        int posicaoHoraria, posicaoAntiHoraria;

        while(input[0] > 0 && input[1] > 0 && input[2] > 0){

            saltoHorario = input[1] - 1;
            saltoAntiHorario = input[2] - 1;

            posicaoHoraria = 1;
            posicaoAntiHoraria = input[0];

            

            lista = new DoubleLinkedList<Integer>();
            for(int i = 1; i <= input[0]; i++){
                lista.pushBack(i);
            }

            System.out.format("  ");
            retirados = new DoubleLinkedList<Integer>();
            while(lista.getSize() > retirados.getSize()){
                posicaoHoraria += saltoHorario;
                if(posicaoHoraria > lista.getSize()){
                    posicaoHoraria = 1;
                }

                System.out.format("%d ", lista.valueInPosition(posicaoHoraria));
                retirados.pushBack(posicaoHoraria);

                posicaoAntiHoraria -= saltoAntiHorario;
                if(posicaoAntiHoraria < 1){
                    posicaoAntiHoraria = lista.getSize() - 1;
                }

                System.out.format("%d,  ", lista.valueInPosition(posicaoHoraria));
                retirados.pushBack(posicaoAntiHoraria);           
            }

            str_input = scan.nextLine().split("");
            for(int i = 0; i < INPUTS; i++){
                input[i] = Integer.parseInt(str_input[i]);
            }
        }
    }
}