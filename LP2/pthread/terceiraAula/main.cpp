#include <stdio.h>
#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

double global;
const int QTD_THREADS{5};
pthread_mutex_t mutex;

void* funcao_thread(void* p){
    int counter{0};

    while(counter < 10000){
        //Protocolo de entrada
        //Seção crítica
        pthread_mutex_lock(&mutex);
        global += 10;
        global *= 1.01;
        pthread_mutex_unlock(&mutex);
        //Protoclo de saída
        counter ++;
    }   
}

int main(void){

    pthread_t threads[QTD_THREADS];

    global = 0;

    for (long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], 0, funcao_thread, 0);
    }

    for (int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    cout << "Valor global: " << global << endl;

}