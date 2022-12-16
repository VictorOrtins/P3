#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define PROCESS 50

/*
    Professor, eu comentei com você que a minha execução estava dando stack smashing detected, só pra você
    lembrar. As respostas teóricas dessa questão estão no txt 
*/

void process_func(int identificador){
    printf("Novo Processo - %d\n", identificador);
    // exit(0);
}

int main(void){
    pid_t originalPid = getpid(); //Pid do processo original é armazenado e poderá ser visto
    //por todos os processos
    pid_t clone_pids[PROCESS]; //array que armazena os pids dos processos clones
    pid_t ret_fork;

    time_t t_inicial = clock(); //tempo  início, antes da criação dos processos

    for(int i = 0; i < PROCESS; i++){
        if (getpid() == originalPid){ //Se o pid for igual ao original
            ret_fork = fork(); //faz o fork e armazena o valor retornado na variável
            if(getpid() == originalPid){ //se for o original
                clone_pids[i] = ret_fork; //armazena na array dos pids dos clones
            }
            else if(getpid() != originalPid){ //Se não
                process_func(i); //chama a função
            }
        }
    }

    
    if(getpid() == originalPid){ //Se o pid for o original
        for(int i = 0; i < PROCESS; i++){
            waitpid(clone_pids[i], NULL, 0); //espera por todos os processos
            kill(clone_pids[i], SIGHUP); //mata-os
        }
        
        time_t t_final = clock(); //tempo final
        double total_t = (double)(t_final - t_inicial)/ CLOCKS_PER_SEC; //total em segundos

        printf("Tempo para criar os processos: %fs\n", total_t);

    }

    return 0;
}