// #include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <iostream>

#define TAM_MAX_SALTO 100
#define TAM_MIN_SALTO 10

using namespace std;

int tam_pista;
int qtd_lebres;

pthread_mutex_t mutex;

typedef struct{
    int i;
    float max_dist;

}Parameters;

void* lebres(void* p){
    long id = (long)p;

    int dist_percorrida_lebre = 0;
    int temp;

    int salto_max = rand() % TAM_MAX_SALTO + 1;
    int salto = 0;

    printf("A lebre %ld iniciou a corrida\n", id);

    while(dist_percorrida_lebre < tam_pista){
        salto = rand() % salto_max + 1;
        dist_percorrida_lebre += salto;
        printf("[lebre-%ld] saltou %dm (%d)\n", id, salto, dist_percorrida_lebre);
    }

    usleep(10);

    printf("[lebre-%ld] venceu\n", id);

    exit(id);
}

int main(int argc, char *argv[]){

    time_t t;
    srand(time(&t));

    if (argc == 1){
        printf("É necessária uma flag para inicialização\n");
        return -1;
    }
    else if(argc == 2 || argc == 3){
        printf("Poucos argumentos\n");
        return -1;
    }
    else if(argc > 4){
        printf("Muitos argumentos\n");
        return -1;
    }
    int param_2 = atoi(argv[2]), param_3 = atoi(argv[3]);

    if (param_2 == 0 || param_3 == 0){
        printf("Argumentos inválidos\n");
        return -1;
    }

    tam_pista = param_3;
    qtd_lebres = param_2;

    if (strcmp(argv[1], "-p") == 0){
        pid_t original_pid = getpid();

        pid_t *pids;
        pids = (pid_t*)malloc(sizeof(pid_t)*qtd_lebres);
        pid_t ret_fork;

        int ret_func;

        for(long i = 0; i < qtd_lebres; i++){
            if(getpid() == original_pid){
                ret_fork = fork();
                if(getpid() == original_pid){
                    pids[i] = ret_fork;
                }
                else{
                    lebres((void*)i);
                }
            }
        }

        wait(NULL);
        printf("[main] [lebre-%d] venceu!\n", ret_func);

        if(getpid() == original_pid){
            for(int i = 0; i < qtd_lebres; i++){
                kill(pids[i], SIGHUP);
            }
        }

    }
    else if (strcmp(argv[1], "-t") == 0){
        
        pthread_t *threads;
        threads = (pthread_t*)malloc(sizeof(pthread_t)*param_2);

        for(long i = 0; i < param_2; i++){
            pthread_create(threads + i, 0, lebres, (void*)i);
        }

        for(int i = 0; i < param_2; i++){
            pthread_join(*(threads + i), NULL);
        }

        exit(0);
    }
    else{
        printf("A flag %s é inválida", argv[1]);
        return -1;
    }
    
}