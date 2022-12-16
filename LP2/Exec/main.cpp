#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc , char **argv){
    printf("Nome do executável: %s", argv[0]);
    if (argc > 1){
        printf("\nProg: %s\n", argv[1]);
    }
    return 0;
}