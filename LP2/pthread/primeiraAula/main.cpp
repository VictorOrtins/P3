#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

using namespace std;

void *thread(void* p){
    long x = (long)p;
    cout << "Sou a thread " << p << endl;
    sleep(5);
    cout << "Saindo..." << endl;

    return p;
}

int main(void){

    cout << "Program init" << endl;
    cout << "How many threads do you want to create?" << endl;
    pthread_t num_threads;
    cin >> num_threads;

    pthread_t *threads;
    threads = (pthread_t*)malloc(sizeof(pthread_t)*num_threads);
    for (long i = 0; i < num_threads; i++){
        pthread_create(threads + i, 0, thread, (void*) i);
    }

    for (int i = 0; i < num_threads; i++){
        pthread_join(*(threads + i), NULL);
    }









}