#include <iostream>
#include <pthread.h>

#define THREADS 10

double var_global; //variável global
pthread_mutex_t mutex; //variável para coordenar o avanço das threads

/*
    Pensando que cada processo possui pelo menos 1 thread, concorrência na computação é quando
    mais de 1 thread está sendo executada pelo sistema operacional. Ela pode acontecer de forma entrelaçada, ou seja,
    quando o sistema operacional faz uso de uma entidade chamada escalonador, que vai decidir qual thread deve ser
    executada em tal momento, ou de maneira paralela, ou paralelismo. O paralelismo pode
    ocorrer localmente, quando a máquina possui um processador multicore, podendo estar executando instruções de mais de 1
    thread, dependendo da quantidade de cores. No caso dos sistemas distribuídos, há mais de uma máquina, ou seja, nesses casos,
    existe de fato mais de um processador para as execuções das instruções de forma paralela.

    Consistência de memória é quando uma região de memória do programa é acessada e atualizada de forma
    consistente, em que cada instrução consegue alterar e ler essa região de memória da forma desejada
    pelo programador. O erro de inconsistência pode ser contornado, no caso de programação concorrente usando threads,
    ao permitir que cada instrução do código seja executada apenas uma thread por vez. Em C, isso é feito
    pelas funções pthread_mutex_lock e pthread_mutex_unlock, como usado nas linhas 30 e 32
*/


void* thread_func(void* p){
    long id = (long)p;
    if(id % 2 == 0){ //Se o id for par
        for(int i = 0; i < 100000; i++){ //100000 vezes
            pthread_mutex_lock(&mutex); //uma thread por vez
            var_global++; //incrementar a variável
            pthread_mutex_unlock(&mutex);
        }
    }
    else{   //Se o id for ímpar 
        for(int i = 0; i < 50000; i++){ //50000 vezes
            pthread_mutex_lock(&mutex); //uma thread por vez
            var_global--; //decrementar a variável
            pthread_mutex_unlock(&mutex);
        }
    }
}

int main(void){
    var_global = 0; //inicialização dar var_global na main, para que seja sabido o valor inicial dessa variável em todas as execuções
    pthread_t clones_pids[THREADS];

    for(long i = 0; i < THREADS; i++){
        pthread_create(&clones_pids[i], 0, thread_func, (void*)i); //criação das threads
    }

    for(int i = 0; i < THREADS; i++){
        pthread_join(clones_pids[i], NULL); //junção das threads com a thread principal
    }

    printf("var_global = %lf\n", var_global);
}