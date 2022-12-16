#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>

#define SIZE_BUFFER 32
#define QTD_CLIENTS 10
#define MY_PORT 9999
int client_sock[QTD_CLIENTS];


void* thread_func(void* p){
    long id = (long)p;
    char send_buffer[SIZE_BUFFER];
    char recv_buffer[SIZE_BUFFER];
    while(1){
        bzero(send_buffer, SIZE_BUFFER);
        strcpy(send_buffer, "Digite algo:");

        int s_ret = send(client_sock[id], send_buffer, SIZE_BUFFER, 0);
        if(s_ret < 0){
            printf("Erro na hora de enviar algo ao cliente (%d)", errno);
            pthread_exit(0);
        }

        int r_ret = recv(client_sock[id], recv_buffer, SIZE_BUFFER, 0);
        if(r_ret < 0){
            printf("Erro na hora de receber mensagem do cliente (%d)\n", errno);
        }

        printf("Mensagem recebida pelo cliente de id %ld: %s\n", id, recv_buffer);
    }

}

int main(void){

    struct sockaddr_in server;
    struct sockaddr_in clients[QTD_CLIENTS];

    int client_len;

    pthread_t threads[QTD_CLIENTS];

    int server_sock;
    long contador_clientes = 0;

    server.sin_family = AF_INET;
    server.sin_port = htons(MY_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    server_sock = socket(AF_INET,SOCK_STREAM, 0);

    if(server_sock < 0){
        printf("Erro na criação do socket do servidor (%d)\n", errno);
        exit(0);
    }

    printf("Socket do servidor criado com sucesso\n");

    // int b_ret = bind(server_sock, (struct sockaddr *)&server, sizeof(server));

    // if(b_ret < 0){
    //     printf("Erro no bind (%d)", errno);
    //     exit(0);
    // }

    // printf("Bind feito com êxito");

    int l_ret = listen(server_sock, QTD_CLIENTS);

    if(l_ret < 0){
        printf("Erro no listen (%d)\n", errno);
        exit(0);
    }

    while(1){
        client_len = sizeof(server);
        client_sock[contador_clientes] = accept(server_sock, (struct sockaddr *)&server, &client_len);

        if(client_sock[contador_clientes] < 0){
            printf("Erro (%d)\n", errno);
            exit(0);
        }

        printf("Conexão recebida pelo cliente %ld\n", contador_clientes + 1);

        pthread_create(&threads[contador_clientes], 0, thread_func, (void*)contador_clientes);

        contador_clientes++;
    }

    close(server_sock);

    return 0;
}