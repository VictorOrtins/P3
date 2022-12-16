/*
(Questão 3 - 5 pontos) Faça um programa em C/C++ que simule o controle de
temperatura de um motor. O programa deverá ter uma variável global do tipo
float chamada temperatura (que armazenará a temperatura em Celsius do motor,
com valor inicial 600 C) e duas threads além da main, realizando funções 
diferentes. A primeira thread  realizará   um   incremento   na   temperatura
com um valor aleatório entre -10 e 90 e depois dormirá 200ms. A segunda 
thread deverá conter um mecanismo que detecte o quanto antes quando o valor da 
temperatura ultrapassar 1000C - quando isso acontecer deve-se dormir 300ms e o
valor da variável temperatura passa a ser 600 novamente.
 
O programa deverá ser finalizado depois de 3 reduções de temperatura do motor.
Comente o código explicando o mecanismo utilizado na segunda thread e qual 
seria a alternativa se não houvesse o requisito de detecção da temperatura de
forma mais imediata possível. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>
#include <pthread.h>
#include <time.h>

#define QTD_THREADS 2

float temperatura_motor = 600;
int contador_reducoes = 0;
int next = 1, number = 1;
int turn[QTD_THREADS];

void* incrementa(void* p){
    long id = (long)p;
    int random;
    while(contador_reducoes < 3){
        while(temperatura_motor >= 1000);
        random = (rand() % 100) - 10;
        turn[id] = atomic_fetch_add(&number,1);
        while(turn[id] != next);
        if(random < 0){
            contador_reducoes++;
        }
    }

}

void* verifica(void* p){
    long id = (long)p;
    while(contador_reducoes < 3){
        while(temperatura_motor < 1000);
        turn[id] = atomic_fetch_add(&number, 1);
        while(turn[id] != next);
        temperatura_motor = 600;
        contador_reducoes++;
        atomic_fetch_add(&next, 1);
    }


}

int main(void){


    return 0;
}