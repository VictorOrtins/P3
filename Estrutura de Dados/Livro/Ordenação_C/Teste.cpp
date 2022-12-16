#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define QUANTIDADE_DE_NUMEROS 5
int main(int argc, int *argv[]){
    int numeros[QUANTIDADE_DE_NUMEROS];
    int numeroAtual;
    printf("Digite %d numeros e tentarei ordena-los em ordem decrescente\n\n", QUANTIDADE_DE_NUMEROS);

    for (int i = 0; i < QUANTIDADE_DE_NUMEROS; i++){
        printf("Digite o numero %d\n", i + 1);
        std::cin >> numeros[i];
    }


    int i, j, x;
    for (i = 2; i <= QUANTIDADE_DE_NUMEROS; i++){
        x = numeros[i];
        j = i - 1;
        numeros[0] = x;
        while (x > numeros[j]){
            numeros[j+1] = numeros[j];
            j--;
        }
        numeros[j+1] = x;
    }

    for (int i = 0; i < QUANTIDADE_DE_NUMEROS; i++){
        std::cout << numeros[i] << std::endl;
    }


    return 0;
}
