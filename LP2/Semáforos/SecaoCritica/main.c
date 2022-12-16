#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define QTD_THREADS 5

int global = 0;
sem_t mutex;

void* thread_func(void* p){
    long id = (long)p;
    int contador = 0;
    while(contador < 1000){
        printf("[%ld] Cheguei no semáforo\n", id);
        sem_wait(&mutex);
        global++;
        sem_post(&mutex);
        sleep(1);
        printf("[%ld] Passei do semáforo\n", id);
        contador++;
    }
}

int main(void){
    pthread_t threads[QTD_THREADS];

    sem_init(&mutex, 0, 1);

    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, thread_func, (void*)i);
    }

    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Global = %d\n", global);

}