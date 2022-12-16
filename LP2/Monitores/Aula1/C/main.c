#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{
    float saldo;
    int cpf;
    pthread_mutex_t mutex;
}Monitor;

#define QTD_OPERACOES 4

typedef struct{
    float saldo;
}return_saldo;


Monitor monitor;

void construtorMonitor(float saldo, int cpf){
    monitor.saldo = saldo;
    monitor.cpf = cpf;
    pthread_mutex_init(&monitor.mutex, 0);
}

void* debito(void* p){
    long saldo = (long)p;

    if(saldo < 0){
        printf("Operação inválida\n");
        return;
    }

    pthread_mutex_lock(&monitor.mutex);
    monitor.saldo -= saldo;
    pthread_mutex_unlock(&monitor.mutex);
}

void* credito(void* p){  
    long saldo = (long)p;
    if(saldo < 0){
        printf("Operação inválida\n");
        return;
    }

    pthread_mutex_lock(&monitor.mutex);
    monitor.saldo += saldo;
    pthread_mutex_unlock(&monitor.mutex);
}

float getSaldo(){
    float result;

    pthread_mutex_lock(&monitor.mutex);
    result = monitor.saldo;
    pthread_mutex_unlock(&monitor.mutex);

    return result;
}

int main(void){
    construtorMonitor(200, 12345);

    pthread_t threads[QTD_OPERACOES];

    pthread_create(&threads[0], 0, credito, (void*)300);
    pthread_create(&threads[1], 0, credito, (void*)500);
    pthread_create(&threads[2], 0, debito, (void*) 900);
    pthread_create(&threads[3], 0, debito, (void*)20);

    for(int i = 0; i < QTD_OPERACOES; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Saldo final: %f\n", getSaldo());

    return 0;
}