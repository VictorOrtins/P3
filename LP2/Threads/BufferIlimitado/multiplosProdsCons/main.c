/*
    Isso aqui vai ser tarefa de Bidu
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define QTD_PRODS 2
#define QTD_CONS 6
#define BUF_SIZE 8

int buf[BUF_SIZE];

int front = 0, rear = 0;
sem_t buffer_empty, buffer_full; //semáforo pra identificar se é produtor ou consumidor
sem_t mutexDeposit, mutexFetch; //semáforo para identificar qual thread produtor/consumidora deve passar

void* producer(void* p){
    long id = (long)p;
    int data;
    while(1){
        printf("[prod %ld] chegando no semáforo de bufferEmpty\n", id);
        sem_wait(&buffer_empty);
        printf("[prod %ld] chegando no semáforo de mutexDeposit\n", id);
        sem_wait(&mutexDeposit);
        data = rand() % 100;
        buf[rear] = data;
        printf("[prod %ld] produzi %d e coloquei no slot %d\n", id, buf[rear], rear);
        sleep(1);
        rear = (rear + 1) % BUF_SIZE;
        sem_post(&mutexDeposit);
        sem_post(&buffer_full);
    }
}

void* consumer(void* p){
    long id = (long)p;
    int a;
    while(1){
        printf("[cons %ld] chegando no semáforo de bufferFull\n", id);
        sem_wait(&buffer_full);
        printf("[cons %ld] chegando no semáforo de mutexFetch\n", id);
        sem_wait(&mutexFetch);
        a = buf[front];
        printf("[cons %ld] consumi %d do slot %d\n", id, a, front);
        sleep(1);
        front = (front + 1) % BUF_SIZE;
        sem_post(&mutexFetch);
        sem_post(&buffer_empty);
    }
} 

int main(void){
    pthread_t producer_threads[QTD_PRODS];
    pthread_t consumer_threads[QTD_CONS];

    time_t t;
    srand(time(&t));

    sem_init(&buffer_empty, 0, BUF_SIZE);
    sem_init(&buffer_full, 0, 0);
    sem_init(&mutexDeposit, 0, 1);
    sem_init(&mutexFetch, 0, 1);

    for(long i = 0; i < QTD_PRODS; i++){
        pthread_create(&producer_threads[i], NULL, producer, (void*)i);
    }

    for(long i = 0; i < QTD_CONS; i++){
        pthread_create(&consumer_threads[i], NULL, consumer, (void*)i);
    }

    for(int i = 0; i < QTD_PRODS; i++){
        pthread_join(producer_threads[i], NULL);
    }

    for(int i = 0; i < QTD_PRODS; i++){
        pthread_join(consumer_threads[i], NULL);
    }

    return 0;
}




