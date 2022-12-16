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
#define QTD_CLIENTS 10
#define RECV_BUFFER_SIZE 32
#define BUFFER_SIZE 1024

pthread_barrier_t barreira;
int clients_sock[QTD_CLIENTS];
char buffer[BUFFER_SIZE];

void* thread_func(void* p){
    long id = (long)p;
    
    char recv_buffer[RECV_BUFFER_SIZE];
    send(clients_sock[id], "START\n", 7, 0);
    while(1){
        bzero(recv_buffer, RECV_BUFFER_SIZE);
        recv(clients_sock[id], recv_buffer, sizeof(recv_buffer), 0);

        printf("Recebi do cliente %ld: %s", id + 1, recv_buffer);

        if(strncmp(recv_buffer, "SHUTDOWN", 8) == 0){
            printf("Cliente %ld desconectado\n", id + 1);
            send(clients_sock[id], "Desconectado do Servidor", sizeof("Desconectado do Servidor"), 0);
            close(clients_sock[id]);
            pthread_barrier_wait(&barreira);
            break;
        }
        
        strcat(buffer, recv_buffer);

        for(int i = 0; i < QTD_CLIENTS; i++){
            send(clients_sock[i], buffer, sizeof(buffer), 0);
        }
    }
}

void* shutdown_func(void* p){
    pthread_barrier_wait(&barreira);
    printf("4 shutdowns recebidos\nServidor desconectado\n");
    exit(0);
}

int main(void){

    struct sockaddr_in server;
    struct sockaddr_in clients[QTD_CLIENTS];

    int server_sock, clients_len[QTD_CLIENTS];

    pthread_t threads[QTD_CLIENTS];
    pthread_t shutdown_thread;

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

    long client_counter = 0;

    pthread_create(&shutdown_thread, 0, shutdown_func, (void*)0);

    pthread_barrier_init(&barreira, 0, 5);
    bzero(buffer, BUFFER_SIZE);

    printf("Servidor criado!\n");
    while(1){
        clients_sock[client_counter] = accept(server_sock, (struct sockaddr*)&clients[client_counter], &clients_len[client_counter]);
        
        printf("Recebi uma conexão do cliente %ld!\n", client_counter + 1);

        if(clients_sock[client_counter] < 0){
            printf("Erro ao estabelecer a conexão\n");
            exit(-1);
        }

        pthread_create(&threads[client_counter], 0, thread_func, (void*)client_counter);
        client_counter++;
    }


    close(server_sock);

    return 0;
}