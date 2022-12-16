/*
(Questão 2 - 5,0 pontos) Faça um programa em C que 4 threads geram uma letra
aleatória (caractere), e as depositam em uma palavra (string) na thread; então,
a thread principal (função  main), depois de aguardar cada uma das threads
depositar sua letra, deve exibir a string gerada. Posteriormente esta string
deverá ser consumida, caractere por caractere, por uma thread consumidora (5a
thread criada além da main). Esta thread receberá a string e contará quantas
vogais nela constam, exibindo o valor. O processo deverá se repetir 5 vezes;
finalmente, o programa deverá exibir o total de vogais de todas as palavras
geradas e encerrar. Use barreiras (pthread.h) e semáforos (semaphore.h) e
comente como suas funções foram utilizadas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define QTD_THREADS 4
#define QTD_VEZES 5

sem_t buf_empty, buf_full;
pthread_barrier_t barrier;

char caracteres[QTD_THREADS];
int qtd_vogais[5];

int main(void){
    sem_init(&buf_empty, 0, QTD_THREADS);
    sem_init(&buf_full, 0, 0);
    return 0;
}