#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>
#include <pthread.h>

#define QTD_CONSUMOS 10

int buf;
int p = 0, c = 0;

void* PROD(void* arg){
    long id = (long)id;
    int a[QTD_CONSUMOS]; //Array passado antes, por algum arquivo ou algo do tipo
    while(p < QTD_CONSUMOS){
        printf("[prod - %ld] esperando p != c\n", id);
        while(p != c);
        buf = a[p];
        printf("[prod - %ld] produziu %d\n", id, buf);
        p++;
    }
}

void* CONS(void* arg){
    long id = (long)id;
    int b[QTD_CONSUMOS]; //Array passado antes, por algum arquivo ou algo do tipo
    while(c < QTD_CONSUMOS){
        printf("[cons - %ld] esperando p <= c\n", id);
        while(p <= c);
        b[c] = buf;
        printf("[cons - %ld] consumiu %d\n", id, buf);
        c++;
    }
}

int main(void){

    pthread_t threads[2];

    pthread_create(&threads[0], NULL, PROD, (void*)0);
    pthread_create(&threads[1], NULL, CONS, (void*)1);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);


    return 0;
}