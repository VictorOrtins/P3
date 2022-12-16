#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define QTD_THREADS 5

int global = 0;
int ticket[QTD_THREADS];
int number = 1, next = 1;

/**
 * Aparentemente certo
*/

void* thread_func(void* p){

    long id = (long)p;
    int contador = 0;



    while(contador < 1000){
        //protocolo de entrada
        ticket[id] = atomic_fetch_add(&number, 1);
        while(ticket[id] != next);
        // printf("[thread %ld] global = %d\n", id, global);
        //
        global++;
        //protocolo de saída
        atomic_fetch_add(&next, 1);
        //
        // printf("[thread %ld] saí da seção crítica\n", id);
        contador++;
    }
    return NULL;
}

int main(void){

    pthread_t threads[QTD_THREADS];


    for(int i = 0; i < QTD_THREADS; i++){
        ticket[i] = 0;
    }

    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, thread_func, (void*)i);
    }

    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("%d\n", global);

    return 0;
}