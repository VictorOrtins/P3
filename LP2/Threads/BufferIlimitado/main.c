#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/types.h>

#define TAM_BUF 8
#define QTD_PROD 1
#define QTD_CONS 1


int buf[TAM_BUF];
sem_t buf_empty, buf_full;
int rear = 0, front = 0;

void* producer(void* p){
    long id = (long)p;
    int data;
    while(1){
        sem_wait(&buf_empty);
        data = rand() % 100;
        buf[rear] = data;
        printf("[prod - %ld] gerou %d e depositou no slot %d\n", id, data, rear);
        rear = (rear + 1) % TAM_BUF;
        sleep(1);
        sem_post(&buf_full);
    }
}

void* consumer(void* p){
    long id = (long)p;
    int a;
    while(1){
        sem_wait(&buf_full);
        a = buf[front];
        printf("[cons - %ld] consumiu %d e depositou no slot %d\n", id, a, front);
        front = (front + 1) % TAM_BUF;
        sleep(1);
        sem_post(&buf_empty);
    }
}


int main(void){
    time_t t;
    srand(time(&t));

    sem_init(&buf_empty, 0, TAM_BUF);
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