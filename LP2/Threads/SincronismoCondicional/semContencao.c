#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdatomic.h>

#define QTD_THREADS 5
int arrive[QTD_CONSUMOS], proceed[QTD_CONSUMOS];

void tarefa(long id){
    sleep(id + 1);
}

void* thread_func(void* p){
    long id = (long)p;
    int contador = 0;
    while(contador < 10){
        arrive[id] = 1;
        while(proceed[id] != 1);
        tarefa(id);
        proceed[id] = 0;
        contador++;
    }
}

void* worker(void* p){
    while(1){
        for(int i = 0; i < QTD_CONSUMOS; i++){
            while(arrive[i] != 0)
        }
    }
}

int main(int argc, char* argv[]){
    pthread_t threads[QTD_CONSUMOS];
    pthread_t coordinator;

    for(int i = 0; i < QTD_CONSUMOS; i++){
        arrive[i] = 0;
        proceed[i] = 0;
    }

    for(long i = 0; i < QTD_CONSUMOS; i++){
        pthread_create(&threads[i], 0, thread_func, (void*)i);
    }

    pthread_create(&coordinator, NULL, worker, NULL);

    for(int i = 0; i < QTD_CONSUMOS; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_join(coordinator, NULL);
}