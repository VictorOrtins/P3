#include <iostream>
#include <thread>
#include <unistd.h>

const int QTD_THREADS = 5;

using std::cout;
using std::endl;
using std::thread;

int thread_func(int a, char b){
    sleep(1 + (int)a);
    cout << "[thread #" << a << "] Recebi " << b << " como parâmetro char" << endl;
    return 0;
}

int main(void){

    thread *threads[QTD_THREADS];
    for (int i = 0; i < QTD_THREADS; i++){
        threads[i] = new thread(thread_func, i, 'A' + i);
    }

    for (int i = 0; i < QTD_THREADS; i++){
        threads[i]->join();
    }

    for (int i = 0; i < QTD_THREADS; i++){
        delete threads[i];
    }
}