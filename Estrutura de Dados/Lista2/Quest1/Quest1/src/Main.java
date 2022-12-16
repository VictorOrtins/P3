import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws EmptyListException, InvalidPositionException {
        DoubleLinkedList<Integer> regions;

        Scanner scan = new Scanner(System.in);
        int m;
        int pulo;
        int posicao;

        int numRegions = 1;
        while(numRegions != 0){
            numRegions = scan.nextInt();

            regions = new DoubleLinkedList<Integer>();
            for(int i = 1; i <= numRegions; i++){
                regions.pushBack(i);
            }

            if(numRegions == 13){
                System.out.println(1);
                continue;
            }


            for(m = 2; m <= numRegions; m++){
                pulo = m - 1;
                posicao = 1;
                // System.out.println("Pulo = " + pulo);
                while(regions.getSize() > 1){
                    // System.out.println("size = " + regions.getSize());
                    // System.out.println("posicao = " + posicao);
                    // System.out.println(regions.printList());

                    if(posicao > regions.getSize() && regions.getSize() > 2){
                        posicao = 1;
                    }
                    else if(posicao > regions.getSize() && regions.getSize() <= 2){
                        posicao %= 2;
                        if(posicao == 0){
                            posicao = 2;
                        }
                        else{
                            posicao = 1;
                        }
                    }

                    regions.remove(posicao);

                    posicao += pulo;

                    if(posicao > regions.getSize()){
                        posicao -= regions.getSize();
                    }
                }
                if(regions.valueInPosition(1) == 13){
                    System.out.println(m);
                    break;
                }

                regions = new DoubleLinkedList<Integer>();
                for(int i = 1; i <= numRegions; i++){
                    regions.pushBack(i);
                }
            }
        }
    }
}
