#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

#define QTD_THREADS 5

int count = 0;

void tarefa(long id){
    sleep(1 + id);
}

void* thread_func(void* p){
    long id = (long)p;
    int contador = 0;
    while(contador < 10){
        printf("[%ld] Realizando a tarefa...\n", id);
        tarefa(id);
        atomic_fetch_add(&count, 1);
        while(count % QTD_CONSUMOS != 0);
        printf("[%ld] Realizei a tarefa [%d]\n", id, count);
        contador++;
    }
}

int main(int argc, char *argv[]){
    pthread_t threads[QTD_CONSUMOS];
    for(long i = 0; i < QTD_CONSUMOS; i++){
        pthread_create(&threads[i], 0, thread_func, (void*)i);
    }

    for(int i = 0; i < QTD_CONSUMOS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Count = %d", count);

    return 0;
}