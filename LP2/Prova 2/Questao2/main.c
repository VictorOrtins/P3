/*
(Questão 2 - 5 pontos) Faça um programa em C/C++ que controle o acesso de 
threads a duas seções críticas diferentes. O programa deverá ter 10 threads,
e duas variáveis globais (x e y) de tipo int, iniciadas com zero. As threads
modificarão em loop e em sequência as duas variáveis, porém a ordem de 
modificação dependerá do valor do índice que receberão no momento de sua 
criação: caso o índice seja par, a thread incrementa o valor da variável x com 
um valor aleatório entre 5 e 100 e dorme 200ms, em seguida incrementa o valor 
da variável y com um valor aleatório entre 1 e 50 e dorme 100ms; caso o índice 
seja ímpar, a thread incrementa o valor da variável x com um valor aleatório 
entre 1 e 30 e dorme 100ms, em seguida incrementa o valor da variável y com 
um valor aleatório entre 15 e 95 e dorme 250ms.
 
Use semáforos (biblioteca semaphore.h) para controlar o acesso às seções 
críticas, (trate o acesso à cada uma das variáveis como uma seção crítica
diferente) e garanta que todas as  threads  incrementem as variáveis globais
dentro de um ciclo de iterações. O programa deverá ser finalizado quando a 
soma dos valores de x e y for maior que 2000. Comente o código explicando 
o que é uma seção crítica, e como foi feito o controle de acesso às duas 
seções críticas do problema usando semáforos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define QTD_THREADS 10

float temp_motor = 0;
sem_t mutex1, mutex2;
int maior_2000 = 0;

float x = 0, y = 0;


void* par(void* p){
    long id = (long)p;
    int random1 = (rand() % 100)+ 5;
    int random2 = (rand() & 50) + 1;
    printf("teste\n");

    while(maior_2000 == 0){
        sem_wait(&mutex1);
        printf("[thread %ld] Adicionando %d a X. X = %f\n", id, random1, x);
        x += random1;
        if(x + y > 2000){
            maior_2000 = 1;
            break;
        }
        usleep(200);
        y += random2;
        printf("[thread %ld] Adicionando %d a Y. Y = %f\n", id, random2, y);
        if(x + y > 2000){
            maior_2000 = 1;
            break;
        }
        usleep(100);
        sem_post(&mutex1);
    }

}

void* impar(void* p){
    long id = (long)p;
    int random1 = (rand() % 30) + 1;
    int random2 = (rand() % 95)+ 15;
    printf("teste\n");

    while(maior_2000 == 0){
        sem_wait(&mutex1);
        x += random1;
        printf("[thread %ld] Adicionando %d a X. X = %f\n", id, random1, x);
        if(x + y > 2000){
            maior_2000 = 1;
            break;
        }
        usleep(100);
        y += random2;
        printf("[thread %ld] Adicionando %d a Y. Y = %f\n", id, random2, y);
        if(x + y > 2000){
            maior_2000 = 1;
            break;
        }
        usleep(250);
        sem_post(&mutex1);
    }

}

int main(void){
    time_t t;
    srand(time(&t));
    pthread_t threads[QTD_THREADS];
    printf("teste\n");

    for(long i = 0; i < QTD_THREADS; i++){
        if(i % 2 == 0){
            pthread_create(&threads[i], 0, par, (void*)i);
        }
        else{
            pthread_create(&threads[i], 0, impar, (void*)i);
        }
    }

    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], 0);
    }

    printf("[main] X = %f, Y = %f\n",x, y);


    return 0;
}