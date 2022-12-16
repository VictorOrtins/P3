// /*
// (Questão 3) Elabore (em código C/C++) um esboço de solução para o problema da seção crítica. 
// Em um sistema bancário múltiplas threads podem realizar operações de débito e crédito no saldo dos clientes – 
// elabore uma solução para a manipulação do saldo utilizando locks, implementando o protocolo de entrada 
// utilizando uma instrução atômica (destaque qual é esta instrução e como ela funciona). 
// */

// #include <stdio.h>
// #include <unistd.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <time.h>
// #include <stdatomic.h>

// #define QTD_CLIENTES 5
// #define QTD_THREADS 3

// int number = 1, next = 1;
// int turn[QTD_CLIENTES][QTD_THREADS];

// float saldo[QTD_CLIENTES];

// typedef struct{
//     int cliente;
//     int j;
//     int operacao;
// }Parameters;

// void* altera_saldo(void* p){
//     Parameters *parameter = p;
//     int cliente = parameter->cliente;
//     int j = parameter->j;
//     int operacao = parameter->operacao;


//     printf("[Thread %d do cliente %d] - mudando o saldo em %d\n", j, cliente, operacao);
//     turn[cliente][j] = atomic_fetch_add(&number, 1); //atômica //protocolo de entrada
//     while(turn[cliente][j] != next); //espera ocupada que serve de lock
//     saldo[cliente] += operacao; //seção crítica
//     atomic_fetch_add(&next, 1); //atômica //protocolo de saída
//     // printf("[Thread %d do cliente %d] - saldo do cliente %.2f\n", j, cliente, saldo[cliente]);
//     sleep(1);
// }


// int main(void){
//     pthread_t threads[QTD_THREADS];
//     Parameters parameters;
//     time_t t;
//     int temp_int;

//     srand(time(&t));
//     long contador = 0;

//     for(int i = 0; i < QTD_CLIENTES; i++){
//         saldo[i] = rand() % 100;
//         printf("[main] - saldo inicial do cliente %d = %f\n", i, saldo[i]);
//     }

//     for(int i = 0; i < QTD_CLIENTES; i++){
//         for(int j = 0; j < QTD_THREADS; j++){
//             temp_int = rand() % 200 - 100;
//             parameters.cliente = i;
//             parameters.j = contador;
//             parameters.operacao = temp_int;

//             pthread_create(&threads[contador], NULL, altera_saldo, &parameters);
//             contador++;
//         }
//     }

//     for(int i = 0; i < contador; i++){
//         pthread_join(threads[i], NULL);
//     }

// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdatomic.h>

#define QTD_THREADS 5

float saldo = 0;
int number = 1, next = 1;
int buf[QTD_THREADS];

typedef struct{
    int i;
    int operacao;
}Arguments;

void* altera_saldo(void* p){
    Arguments *parameters = p;

    int id = parameters->i;
    int operacao = parameters->operacao;
    while(1){
        buf[id] = atomic_fetch_add(&number, 1);
        while(buf[id] != next){
        // printf("teste");
        };
        printf("[Thread %d] Adicionando %d ao saldo\n", id, operacao);
        saldo += operacao;
        printf("[Thread %d] Saldo agora = %f\n", id, saldo);
        atomic_fetch_add(&next, 1);
    }


}

int main(void){
    pthread_t threads[QTD_THREADS];
    Arguments parameters;
    time_t t;

    srand(time(&t));

    saldo = (rand() % 200) - 100;
    printf("[Main] Saldo no início = %f\n\n", saldo);

    for(long i = 0; i < QTD_THREADS; i++){
        parameters.i = i;
        parameters.operacao = rand() % 200 - 100;

        pthread_create(&threads[i], 0, altera_saldo, &parameters);
    }

    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], 0);
    }

    return 0;
}