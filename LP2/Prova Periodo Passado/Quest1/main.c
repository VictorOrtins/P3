/*
    (Questão 1 - 10 pontos) Faça um programa em C/C++ que crie um servidor TCP que
atender os requisitos listados a seguir.

	1) Trate até 8 conexões simultâneas de clientes na porta 9900;

	2) Cada novo cliente deve receber uma string de boas vindas ao se conectar ao
	servidor (“BEM-VINDO”);

	3) O servidor tratará strings enviadas pelos clientes como comandos, e
	retornará o resultado para eles de acordo com os comandos, como descrito a
	seguir. Os seguintes comandos devem ser suportados:

		a) "RNDNUM\n" - o servidor irá gerar e retornar um valor aleatório
	        entre 0 e 1000;

		b) "CRTIME\n" - o servidor retornará a data e hora corrente;

		c) "FINISH\n" - o servidor finaliza a conexão do cliente;

		d) "SHTDWN\n" - o servidor está finalizado (fim do programa);

	4) O servidor deve armazenar todas as solicitações realizadas pelos clientes
	em um arquivo de texto chamado "log.txt". O acesso de escrita e leitura a esse
	arquivo deve ser feito através de um monitor.

A saída do seu programa deve ser bem eletrônica, de forma a mostrar o que está
controle em cada momento relevante. Teste o servidor com múltiplos clientes,
usando instâncias de telnet ou nc (netcat).
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define SERVER_PORT 9001
#define QTD_CLIENTS 8
#define RECV_BUFFER_SIZE 60
#define FILENAME "log.txt"

typedef struct{
    FILE* arq;
    pthread_mutex_t lock;
}Monitor;

Monitor monitor;

int server_sock;
long clients_sock[QTD_CLIENTS];


void* thread_func(void* p){
    long client_sock = (long)p;
    char recv_buffer[RECV_BUFFER_SIZE];

    time_t t;
    srand(time(&t));

    time(&t);

    int valor_aleatorio;
    struct tm *hora_sistema;
    hora_sistema = localtime(&t); 


    send(client_sock, "BEM-VINDO\n", 10, 0);
    while(1){
        bzero(recv_buffer, RECV_BUFFER_SIZE);
        recv(client_sock, recv_buffer, sizeof(recv_buffer), 0);

        printf("Recebi do cliente %ld: %s\n", client_sock, recv_buffer);
        if(strncmp(recv_buffer, "RNDNUM", 6) == 0){
            bzero(recv_buffer, RECV_BUFFER_SIZE);

            sprintf(recv_buffer, "Cliente %ld: ", client_sock);
            strcat(recv_buffer, "RNDNUM\n");

            pthread_mutex_lock(&monitor.lock);
            fputs(recv_buffer, monitor.arq);
            pthread_mutex_unlock(&monitor.lock);

            bzero(recv_buffer, RECV_BUFFER_SIZE);

            valor_aleatorio = rand() % 100;
            sprintf(recv_buffer, "%d\n", valor_aleatorio);

            printf("Valor enviado para cliente %ld: %d\n", client_sock, valor_aleatorio);
            send(client_sock, recv_buffer, sizeof(recv_buffer), 0);            
        }
        else if(strncmp(recv_buffer, "CRTIME", 6) == 0){
            bzero(recv_buffer, RECV_BUFFER_SIZE);

            sprintf(recv_buffer, "Cliente %ld: ", client_sock);
            strcat(recv_buffer, "CRTIME\n");

            pthread_mutex_lock(&monitor.lock);
            fputs(recv_buffer, monitor.arq);
            pthread_mutex_unlock(&monitor.lock);

            bzero(recv_buffer, RECV_BUFFER_SIZE);

            sprintf(recv_buffer, "%d/%d/%d %d:%d:%d\n", hora_sistema->tm_mday, hora_sistema->tm_mon + 1, hora_sistema->tm_year + 1900, hora_sistema->tm_hour, hora_sistema->tm_min, hora_sistema->tm_sec);
            printf("Hora do sistema enviado para o cliente\n");
            send(client_sock, recv_buffer, sizeof(recv_buffer), 0);
        }
        else if(strncmp(recv_buffer, "FINISH", 6) == 0){
            bzero(recv_buffer, RECV_BUFFER_SIZE);

            sprintf(recv_buffer, "Cliente %ld: ", client_sock);
            strcat(recv_buffer, "FINISH\n");

            pthread_mutex_lock(&monitor.lock);
            fputs(recv_buffer, monitor.arq);
            pthread_mutex_unlock(&monitor.lock);

            send(client_sock, "Finalizando conexão\n", sizeof("Finalizando conexão\n"), 0);
            printf("Finalizando conexão com cliente %ld\n", client_sock);
            close(client_sock);
            break;
        }else if(strncmp(recv_buffer, "SHTDWN", 6) == 0){
            bzero(recv_buffer, RECV_BUFFER_SIZE);

            sprintf(recv_buffer, "Cliente %ld: ", client_sock);
            strcat(recv_buffer, "SHTDWN\n");

            pthread_mutex_lock(&monitor.lock);
            fputs(recv_buffer,  monitor.arq);
            pthread_mutex_unlock(&monitor.lock);

            printf("SHTDWN recebido\nFinalizando Servidor\n");

            for(int i = 0; i < QTD_CLIENTS; i++){
                close(clients_sock[i]);
            }

            close(server_sock);
            exit(0);
        }
    }
}

int main(void){
    struct sockaddr_in server;
    struct sockaddr_in clients[QTD_CLIENTS];

    int clients_len[QTD_CLIENTS];

    pthread_t threads[QTD_CLIENTS];
    pthread_t shutdown_thread;

    long clients_sock[QTD_CLIENTS];

    pthread_mutex_init(&monitor.lock, 0);
    monitor.arq = fopen(FILENAME, "w");

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0){
        printf("Erro ao criar o socket do servidor (%d)\n", errno);
        exit(-1);
    }

    if(bind(server_sock, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Erro no bind (%d)\n", errno);
        exit(-1);
    }

    if(listen(server_sock, QTD_CLIENTS) < 0){
        printf("Erro no listen (%d)\n", errno);
        exit(-1);
    }

    int client_counter = 0;

    printf("Servidor criado!\n");
    while(1){
        clients_sock[client_counter] = accept(server_sock, (struct sockaddr*)&clients[client_counter], &clients_len[client_counter]);
        
        printf("Recebi uma conexão do cliente %d!\n", client_counter + 1);

        if(clients_sock[client_counter] < 0){
            printf("Erro ao estabelecer a conexão\n");
            exit(-1);
        }

        pthread_create(&threads[client_counter], 0, thread_func, (void*)clients_sock[client_counter]);
        client_counter++;
    }


    close(server_sock);

    return 0;
}