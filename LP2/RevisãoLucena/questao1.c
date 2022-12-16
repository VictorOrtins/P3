/*
(Questão 1 - 5,0 pontos) Faça um programa em C/C++ que controle o acesso de
duas filas de threads a duas seções críticas diferentes. O programa deverá
possuir duas variáveis globais (x e y) de tipo float, iniciadas com zero, que
serão manipuladas por 5 threads cada (num total de 10 threads). As threads de
indices pares deverão executar uma função que manipule o valor da variável x,
incrementando-a com um valor aleatório entre 1 e 5, depois dormindo 250ms; as
threads com indice ímpar executarão uma função que manipula o valor da variável
y, incrementando-a com valor com aleatório entre 2 e 25 e depois dormir 300ms.

Implemente uma solução para o problema da seção crítica que atenda as 4
propriedades de uma solução ideal, que use espera ocupada e que garanta que
todas as threads incrementem as duas variáveis globais dentro de um ciclo de
iterações. O programa deverá ser finalizado quando a soma dos valores de x e y
for  maior que 100. Comente o código explicando como foi feito o controle de
acesso às duas seções críticas, explicando qual a função atômica utilizada
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>
#include <pthread.h>
#include <time.h>

#define QTD_THREADS 10
int turn[QTD_THREADS];
int next = 1, number = 1;

float x = 0, y = 0;

void* par(void* p){
    long id = (long)p;
    int random = (rand() % 5)+ 1;

    while(1){
        // printf("teste 1");
        turn[id] = atomic_fetch_add(&number, 1);
        while(turn[id] != next);
        if(x + y > 100){
            printf("aqui");
            break;
        }
        printf("[thread %ld] Gerei %d. X + Y= %f\n", id, random, x+y);
        x += random;
        atomic_fetch_add(&next, 1);
        printf("teste 1");
    }

}

void* impar(void* p){
    long id = (long)p;
    int random = (rand() % 25)+ 2;

    while(1){
        // printf("teste 2");
        turn[id] = atomic_fetch_add(&number, 1);
        while(turn[id] != next);
        if(x + y > 100){
            printf("aqui");
            break;
        }
        printf("[thread %ld] Gerei %d. X + Y = %f\n", id, random, x+y);
        y += random;
        // usleep(300);
        atomic_fetch_add(&next, 1);
        printf("teste 2");
    }

}

int main(void){
    time_t t;
    srand(time(&t));
    pthread_t threads[QTD_THREADS];

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


    return 0;
}