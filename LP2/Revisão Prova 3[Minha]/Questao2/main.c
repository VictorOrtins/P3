#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define FILE_NAME "arquivo.bin"
#define QTD_OPERACOES 5
#define STRING_SIZE 255

typedef struct{
	int operacao;
	char codigo;
	float valor;
}operacao_bancaria;

typedef struct{
    pthread_mutex_t lock;
    FILE *arq;
}Monitor;

Monitor monitor;

void* thread_func(void* p){
    operacao_bancaria *op = (operacao_bancaria*)p;

    pthread_mutex_lock(&monitor.lock);
    printf("Operação: %d\n", op->operacao);
    printf("Código: %c\n", op->codigo);
    printf("Valor: %f\n", op->valor);
    fwrite(op, sizeof(operacao_bancaria), 1, monitor.arq);
    pthread_mutex_unlock(&monitor.lock);
}

int main(void){
    operacao_bancaria operacoes[QTD_OPERACOES];
    pthread_t threads[QTD_OPERACOES];

    pthread_mutex_init(&monitor.lock, 0);
    monitor.arq = fopen(FILE_NAME, "w");

    time_t t;
    srand(time(&t));

    for(int i = 0; i < QTD_OPERACOES; i++){
        operacoes[i].codigo = 'A' + rand() % 26;
        operacoes[i].operacao = rand() % 5;
        operacoes[i].valor = (rand() % 150) + 25;
        // printf("%c %d %f\n", operacoes[i].codigo, operacoes[i].operacao, operacoes[i].valor);
    }

    for(int i = 0; i < QTD_OPERACOES; i++){
        pthread_create(&threads[i], 0, thread_func, (void*)&operacoes[i]);
    }

    for(int i = 0; i < QTD_OPERACOES; i++){
        pthread_join(threads[i], NULL);
    }


    fclose(monitor.arq);

    return 0;
}