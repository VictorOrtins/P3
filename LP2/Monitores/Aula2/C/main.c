#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define TAM_BUFFER 50

pthread_mutex_t mutex;


typedef struct{
    int *buffer;
    int rear, front;
    int tam_buffer;
    sem_t buffer_empty, buffer_full;
}Monitor;

Monitor monitor;

void construtor_monitor(){

    monitor.tam_buffer = TAM_BUFFER;
    monitor.rear = 0;
    monitor.front = 0;

    monitor.buffer = (int*)malloc(sizeof(int)*monitor.tam_buffer);
    sem_init(&monitor.buffer_empty, 0, monitor.tam_buffer*2);
    sem_init(&monitor.buffer_full, 0, 0);
}

void deposit(int data){

    sem_wait(&monitor.buffer_empty);

    monitor.buffer[monitor.rear] = data;
    monitor.rear = (monitor.rear + 1) % monitor.tam_buffer;

    sem_post(&monitor.buffer_full);

}

int fetch(){
    int result;

    sem_wait(&monitor.buffer_full);

    result = monitor.buffer[monitor.front];
    monitor.front = (monitor.front + 1) % monitor.tam_buffer;

    sem_wait(&monitor.buffer_empty);

    return result;
}

void* producer(void* p){
    int data;
    for(int i = 0; i < TAM_BUFFER; i++){
        data = rand() % 30;
        deposit(data);

        pthread_mutex_lock(&mutex);
        printf("[Producer %d] Depositei %d no buffer\n", i, data);
        pthread_mutex_unlock(&mutex);
    }
}

void* consumer(void* p){
    int data;
    for(int i = 0; i < TAM_BUFFER; i++){
        data = fetch();

        pthread_mutex_lock(&mutex);
        printf("[Consumer %d] Consumi %d do buffer\n", i, data);
        pthread_mutex_unlock(&mutex);
    }
}

int main(void){
    construtor_monitor();

    time_t t;
    srand(time(&t));

    pthread_mutex_init(&mutex, 0);

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, 0, producer, NULL);
    pthread_create(&consumer_thread, 0, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}