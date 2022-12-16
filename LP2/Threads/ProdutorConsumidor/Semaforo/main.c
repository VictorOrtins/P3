#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/types.h>

#define QTD_PROD 4
#define QTD_CONS 4

int buf;
sem_t buf_empty, buf_full;

void* producer(void* p){
    long id = (long)p;
    int value;
    while(1){
        sem_wait(&buf_empty);
        value = rand() % 100;
        buf = value;
        printf("[prod - %ld] gerou %d\n", id, buf);
        sleep(1);
        sem_post(&buf_full);
    }
}

void* consumer(void* p){
    long id = (long)p;
    int a;
    while(1){
        sem_wait(&buf_full);
        a = buf;
        printf("[prod - %ld] consumiu %d\n", id, a);
        sleep(1);
        sem_post(&buf_empty);
    }
}


int main(void){
    time_t t;
    srand(time(&t));

    sem_init(&buf_empty, 0, QTD_PROD);
    sem_init(&buf_full, 0, 0);

    pthread_t threads_prods[QTD_PROD];
    pthread_t threads_cons[QTD_CONS];

    for(long i = 0; i < QTD_PROD; i++){
        pthread_create(&threads_prods[i], NULL, producer, (void*)i);
    }

    for(long i = 0; i < QTD_CONS; i++){
        pthread_create(&threads_cons[i], NULL, consumer, (void*)i);
    }

    for(int i = 0; i < QTD_PROD; i++){
        pthread_join(threads_prods[QTD_PROD], NULL);
    }

    for(int i = 0; i < QTD_PROD; i++){
        pthread_join(threads_cons[QTD_CONS], NULL);
    }


    return 0;
}