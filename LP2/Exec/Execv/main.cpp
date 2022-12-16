#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

    char* my_args[2] = {"../main", "STRING_TESTS"};

    printf("Sou o programa execv\n");
    int x = 0;
    while (x < 99999){
        x++;
    }

    int ret_fork = fork();
    if (ret_fork == 0){
        execv("../main", my_args); //Pega o contexto desse outro processo e copia neste.
        //Por isso, o programa que executou execv não executa o último printf.
    }
    
    printf("[original] Ainda sou o programa execv\n");

    return 0;
}