#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define QTD_THREADS 5

int global_var = 0;

void* thread_func(void* p){
    long id = (long)p;
    printf("[thread#%ld] init\n", id);
    sleep(1 + (int)id);

    long ran = rand() % 100;
    printf("[thread#%ld] Número randômico: %ld\n",id,  ran);

    int count = 0;
    do{

        global_var++;
        count++;

    }while(count < 1000000);

    printf("[thread #%ld] Global_var = %d", id, global_var);
    printf("[thread #%ld] end\n", id);

    return (void*)ran;
}

int main(void){
    time_t t;
    srand(time(&t));

    printf("[main] init\n");

    pthread_t threads[QTD_THREADS];
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(threads + i, 0, thread_func, (void*)i);
    }

    for (int i = 0; i < QTD_THREADS; i++){
        pthread_join(*(threads + i), NULL);
    }

    printf("[main] Global_Var = %d\n", global_var);

    printf("[main] end\n");
    // sleep(10);


    return 0;
}