#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define QTD_THREADS 2

sem_t arrive1, arrive2;

void tarefa(long id){
    sleep(id + 1);
}

void* worker1(void* p){
    long id = (long)p;
    int contador = 0;
    while(contador < 10000){
        printf("[%ld] realizando a tarefa...\n", id);
        tarefa(id);
        printf("[%ld] cheguei no semáforo\n", id);
        sem_post(&arrive1);
        sem_wait(&arrive2);
        printf("[%ld] sai do semáforo\n", id);
        contador++;
    }
}

void* worker2(void* p){
    long id = (long)p;
    int contador = 0;
    while(contador < 10000){
        printf("[%ld] realizando a tarefa...\n", id);
        tarefa(id);
        printf("[%ld] cheguei no semáforo\n", id);
        sem_post(&arrive2);
        sem_wait(&arrive1);
        printf("[%ld] sai do semáforo\n", id);
        contador++;
    }
}

int main(void){

    pthread_t threads[QTD_THREADS];

    sem_init(&arrive1, 0, 0);
    sem_init(&arrive2, 0, 0);

    pthread_create(&threads[0], NULL, worker1, (void*)0);
    pthread_create(&threads[1], NULL, worker2, (void*)1);

    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}