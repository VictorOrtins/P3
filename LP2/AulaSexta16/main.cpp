#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/wait.h>

int main(void){

    pid_t clone_pid;
    int pid_original{getpid()};
    int my_var{};
    int exe_status{};

    clone_pid = fork();

    if (getpid() == pid_original){
        printf("[original] Esse é o processo original\n");
        printf("[original] Esse é o PID do processo: %d\n",getpid());
        printf("[original] Esse é o PID do processo filho: %d\n", clone_pid);
        printf("[original] Esse é o PID do processo pai: %d\n", getppid());
        printf("[original] Esperando processo clone...\n");
        wait(&exe_status);
        printf("[original] Número passado pelo processo clone: %d\n", exe_status); //Vai aparecer
        //um número diferente porque tem uma macro que formata o número do jeito certo.
        printf("[original] Fim do processo!\n");
    }
    else{
        printf("[clone] Esse é o processo clone\n");
        printf("[clone] Esse é o PID do processo: %d\n", getpid());
        printf("[clone] Esse é o PID do processo pai: %d\n", getppid());
        printf("[clone] Digite um número entre 0-255\n");
        scanf("%d", &my_var);
        printf("my_var: %d\n", my_var);
        printf("[clone] Passando esse número para o processo original...\n");
        exit(my_var);
    }

    return 0;
}
