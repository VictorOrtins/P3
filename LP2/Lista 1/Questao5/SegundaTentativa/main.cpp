#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define THREAD_MODE "-t"
#define PROCESS_MODE "-p"

int main(int argc, char *argv[]){
    
    if(argc < 4){
        printf("Too few arguments passed\n");
        return -1;
    }
    else if(argc > 4){
        printf("Too many arguments passed\n");
        return -1;
    }

    int arg_2{atoi(argv[2])}, arg_3{atoi(argv[3])};

    if(strcmp(argv[1], THREAD_MODE) == 0){
        printf("Calling threads program\n");
        execv("/threads/main.cpp", argv);
    }
    else if (strcmp(argv[1], PROCESS_MODE) == 0){
        printf("Calling process program\n");
        execv("/processos/main.cpp", argv);
    }
    else if(argv[1][0] != '-'){
        printf("Flag needed\n");
        return -1;
    }
    else{
        printf("The flag %s was not identified\n", argv[1]);
        return -1;
    }

    printf("Teste\n");

    return 0;
}