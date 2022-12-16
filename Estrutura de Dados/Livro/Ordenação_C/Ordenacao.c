#include <stdio.h>
#include <stdlib.h>

#define QUANTIDADE_DE_NUMEROS 5

int main(int argc, int *argv[]){
    int numeros[QUANTIDADE_DE_NUMEROS];
    int numeroAtual;
    printf("Digite %d numeros e tentarei ordena-los em ordem decrescente\n\n", QUANTIDADE_DE_NUMEROS);


    for (int i = 0; i < QUANTIDADE_DE_NUMEROS; i++){
        printf("Digite o numero %d\n\n", i + 1);
        scanf("%d", &numeroAtual);;

        if (i == 0){
            numeros[i] = numeroAtual;
            continue;
        }

        for(int j = i - 1; j >= 0; j--){
            if (numeroAtual >= numeros[j]){
                int temporario = numeros[j];
                numeros[j] = numeroAtual;
                numeros[j + 1] = temporario;
            }
            else{
                numeros[j+1] = numeroAtual;
                break;
            }
        }
    }


    for (int i = 0; i < QUANTIDADE_DE_NUMEROS; i++){
        printf("%d\n", numeros[i]);
    }


    return 0;
}


