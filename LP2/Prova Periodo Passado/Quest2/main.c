/*
(Questão 2 - 4 pontos) Faça um programa em C/C++ que possa ser usado como
cliente do servidor implementado na questão anterior. Comente o código
explicando a diferença entre os papéis de cliente e servidor, ressaltando o que
chamadas feitas no código são necessárias no contexto específico do protocolo TCP.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#define SERVER_PORT 9001
#define BUFFER_SIZE 64

int main(){
    unsigned short port;

    char send_buffer[BUFFER_SIZE];
    char recv_buffer[BUFFER_SIZE];
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

    /*
        Bidu disse que é bom dar bind no cliente tbm, porém eu não consegui com o vídeo
        do indiano, então tenta ajeitar depois
    */

    // int b_ret = bind(client_sock, (struct sockaddr *)&client, sizeof(client));

    // if(b_ret == -1){
    //     printf("bind error (%d)\n", errno);
    //     exit (0);
    // }

    // printf("Bind completed\n");

    int c_ret = connect(client_sock, (struct sockaddr *)&client, sizeof(client));
    if(c_ret < 0){
        printf("Connection failed\n");
        exit(0);
    }

    printf("Conectado ao servidor\n");
    while(1){
        
        bzero(recv_buffer, BUFFER_SIZE);
        int r_ret = recv(client_sock, recv_buffer, BUFFER_SIZE, 0);
        printf("Recebido do Servidor: %s\n", recv_buffer);

        bzero(send_buffer, BUFFER_SIZE);
        printf("Digite um comando para o servidor: ");
        scanf("%s", send_buffer);

        int s_ret = send(client_sock, send_buffer, strlen(send_buffer), 0);

        if(s_ret < 0){
            printf("Error while sending message\n");
            exit(0);
        }

        if(strcmp(send_buffer, "SHTDWN") == 0 || strcmp(send_buffer, "FINISH") == 0){
            break;
        }
    }


    close(client_sock);
    printf("Disconnected from the server\n");

    return 0;
}