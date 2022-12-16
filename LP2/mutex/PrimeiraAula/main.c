//2 threads

#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

int in1 = 0, in2 = 0;
int global = 0;

/*
    Tá errado, geralmente dá um resultado bem diferente do que deveria dar
*/

void* thread_func1(void* p){
    int contador = 0;
    while(contador < 1000000){
        //protocolo de entrada
        while(in2 == 1);
        atomic_flag_test_and_set(&in1);
        //
        global++;
        //protocolo de saída
        in1 = 0;
        //
        contador++;
    }

    return NULL;
}

void* thread_func2(void* p){
    int contador = 0;
    while(contador < 1000000){
        //protocolo de entrada
        while(in1 == 1);
        atomic_flag_test_and_set(&in2);
        //
        global++;
        //protocolo de saída
        in2 = 0;
        //
        contador++;
    }

    return NULL;
}

int main(void){

    pthread_t thread1, thread2;

    pthread_create(&thread1, 0, thread_func1, (void*)1);
    pthread_create(&thread2, 0, thread_func2, (void*)2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("%d\n", global);

    return 0;
}