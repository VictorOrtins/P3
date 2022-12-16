#include <iostream>
#include <pthread.h>
#include <time.h>

#define THREADS 50

void* thread_func(void* p){
    long id = (long)p; //id da thread

    printf("Nova thread - %ld\n", id);
}

int main(void){

    pthread_t threads[THREADS]; //Criação do array que vai armazenar das threads

    time_t t_inicial = clock(); //Antes de criar as threads, armazeno o valor do clock
    //para saber o tempo no início

    for(long i = 0; i < THREADS; i++){
        pthread_create(&threads[i], 0, thread_func, (void*)i); //Cria as 50 threads
    }

    for(int i = 0; i < THREADS; i++){
        pthread_join(threads[i], NULL); //Aqui, todas as threads são juntadas com a main, de forma equivalente 
        //ao que seria feito com waitpid no caso de processos
    }

    time_t t_final = clock(); //Depois da criação de todas as threads, o valor do clock
    //é armazenado

    double total_t = (double)(t_final - t_inicial)/ CLOCKS_PER_SEC; //Valor total da duração da criação
    //das threads, em segundos

    printf("Tempo de criar as threads: %fs\n", total_t); //print do tempo que foi necessário para criar as threads

    return 0;
}