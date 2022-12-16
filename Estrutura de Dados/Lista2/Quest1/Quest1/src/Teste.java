import java.util.ArrayList;
import java.util.Scanner;

public class Teste {
    public static void main(String[] args) {
        ArrayList<Integer> regions;

        Scanner scan = new Scanner(System.in);

        int m;
        int pulo;
        int posicao;

        int numRegions = 1;
        while(numRegions != 0){
            numRegions = scan.nextInt();

            regions = new ArrayList<Integer>();
            for(int i = 1; i <= numRegions; i++){
                regions.add(i);
            }

            if(numRegions == 13){
                System.out.println(1);
                continue;
            }


            for(m = 2; m <= numRegions; m++){
                pulo = m - 1;
                posicao = 0;
                System.out.println("Pulo = " + pulo);
                while(regions.size() > 1){
                    // System.out.println("size = " + regions.size());
                    // System.out.println("posicao = " + posicao);
                    // System.out.println(regions.printList());

                    if(regions.size() == 2){
                        System.out.println("size = " + regions.size());
                        System.out.println("posicao = " + posicao);
                    }

                    if(posicao > regions.size() && regions.size() > 2){
                        posicao = 0;
                    }
                    else if(posicao > regions.size() && regions.size() <= 2){
                        posicao %= 2;
                        if(posicao == 0){
                            posicao = 1;
                        }
                        else{
                            posicao = 0;
                        }
                    }

                    regions.remove(posicao);

                    posicao += pulo;

                    if(posicao >= regions.size()){
                        posicao -= regions.size();
                    }
                }
                if(regions.get(0) == 13){
                    System.out.println(m);
                    break;
                }

                regions = new ArrayList<Integer>();
                for(int i = 1; i <= numRegions; i++){
                    regions.add(i);
                }
            }
        }
    }
}
