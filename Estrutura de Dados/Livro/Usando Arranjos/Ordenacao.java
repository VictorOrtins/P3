public class Ordenacao{
    public static void main(String[] args) {
        int[] numeros = {223,554,585,264,11,992,228,799,926,380};
        System.out.println(numeros);
         
        numeros = insertionSort(numeros);
        for (int i = 0; i < numeros.length; i++){
            System.out.println(numeros[i]);
        }
        
    }

    public static int[] insertionSort(int[] vetor){
        int tamanho = vetor.length;

        int vetorTemporario[] = vetor;
        vetorTemporario[0] = vetor[0];

        for (int i = 1; i < tamanho; i++){
            int numeroAtual = vetor[i];
            for (int j = i - 1; j >= 0; j--){
                if (numeroAtual >= vetor[j]){
                    int temp = vetor[j];
                    vetorTemporario[j] = numeroAtual;
                    vetorTemporario[j + 1] = temp;
                }
                else{
                    vetorTemporario[j + 1] = numeroAtual;
                    break;
                }
            }
        }

        return vetorTemporario;
    }
}
