#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>

/*
    Tá errado, em algumas instâncias há um errinho besta de escalonamento
    Esse problema caia na história que Bidu falou de contenção de memória, então talvez
    o erro seja relacionado a isso. Então seria um problema tecnicamente previsto que foi corrigido
    com o algoritmo do ticket
*/

#define QTD_THREADS 5
int pass = 0;
int global = 0;

void* thread_func(void* p){
    long id = (long)p;
    int contador = 0;

    while(contador < 100){
        printf("global = %d\n", global);
        while(pass);
        pass = 1;
        global++;
        pass = 0; 
        contador++;
   }



}

int main(void){

    pthread_t threads[QTD_THREADS];
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, thread_func, (void*)i);
    }

    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("%d\n", global);

    return 0;
}