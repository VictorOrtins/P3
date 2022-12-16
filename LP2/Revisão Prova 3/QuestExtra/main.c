/*
UNIVERSIDADE FEDERAL DA PARAÍBA – CENTRO DE INFORMÁTICA
LPII - Programação Concorrente - 2022.1
Prof. Carlos Eduardo Batista
Pontuação: vale 2,0 pontos (para segunda ou terceira prova)
Entrega: por e-mail (bidu @ ci.ufpb.br) até 09h59 12/12/2022


1) Faça um programa em C/C++ que implemente um cliente para
o servidor da primeira questão da revisão. Faça o programa 
solicitar para o usuário a mensagem a enviar e exiba as
mensagens recebidas do servidor. 
O programa deverá ser finalizado caso o usuário envie a string "EXIT".
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#define SERVER_PORT 9998
#define EXIT_KEY "SHUTDOWN"

int main(){
    unsigned short port;
    char send_buffer[32];
    char recv_buffer[32];
    int client_len;

    struct sockaddr_in client;

    int client_sock;

    client_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (client_sock == -1){
        printf("Socket error (%d)\n", errno);
        exit (0);
    }

    printf("TCP client socket created\n");
    

    client.sin_family = AF_INET;
    client.sin_port = htons(SERVER_PORT);
    client.sin_addr.s_addr = INADDR_ANY;


    int c_ret = connect(client_sock, (struct sockaddr *)&client, sizeof(client));
    if(c_ret < 0){
        printf("Connection failed\n");
        exit(0);
    }

    printf("Connected to the server\n");

    while(1){
        bzero(recv_buffer, 32);

        int r_ret = recv(client_sock, recv_buffer, strlen(recv_buffer), 0);

        if(r_ret < 0){
            printf("Receiving error %d\n", errno);
            exit(0);
        }

        printf("Recebi do servidor: %s\n", recv_buffer);


        bzero(send_buffer, 32);
        printf("Type what you want to send to the server: ");
        scanf("%s", send_buffer);

        int s_ret = send(client_sock, send_buffer, strlen(send_buffer), 0);

        if(strcmp(send_buffer, EXIT_KEY) == 0){
            break;
        }

        if(s_ret < 0){
            printf("Error while sending message\n");
            exit(0);
        }
    }

    close(client_sock);
    printf("Disconnected from the server\n");

    return 0;

}