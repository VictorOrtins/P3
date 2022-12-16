#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#define MY_PORT 9998
#define SIZE_BUFFER 32

int main(){
    unsigned short port;
    char recv_buffer[SIZE_BUFFER];
    int client_len;

    struct sockaddr_in server;
    struct sockaddr_in client;

    int server_sock;
    int client_sock;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (server_sock == -1){
        printf("Socket error (%d)\n", errno);
        exit(0);
    }

    printf("TCP server socket created\n");

    /*
        Isso aqui aparentemente só é executado após o cliente conseguir se conectar com o servidor
    */
    
    server.sin_family = AF_INET;
    server.sin_port = htons(MY_PORT);
    server.sin_addr.s_addr = INADDR_ANY;


    int b_ret = bind(server_sock, (struct sockaddr *)&server, sizeof(server));
    
    if(b_ret == -1){
        printf("bind error (%d)\n", errno);
        exit (0);
    }

    printf("Bind to port %d\n", MY_PORT);

    int l_ret = listen(server_sock, 10); //Último parâmetro é o tamanho da fila de clientes

    if(l_ret == -1){
        printf("listen error (%d)\n", errno);
    }

    printf("Listening...\n");

    client_len = sizeof(client);

    client_sock = accept(server_sock, (struct sockaddr *)&client, &client_len);

    if(client_sock == -1){
        printf("accept error (%d)\n", errno);
        exit(0);
    }

    printf("Recebi uma conexão\n");
    printf("Endereço: %d\n", client.sin_addr.s_addr);
    
    while(1){
        char send_buf[14] = "Bem vindo!\n";

        int s_ret = send(client_sock,"Bem Vindo!", sizeof("Bem Vindo!"), 0);

        if(s_ret == -1){
            printf("send error\n");
        }
        
        bzero(recv_buffer, SIZE_BUFFER);

        //Essa função recv garante que o cliente possa digitar algo para o servidor
        int r_ret = recv(client_sock, recv_buffer, sizeof(recv_buffer), 0);
        printf("Recebi do cliente: %s\n", recv_buffer);
    }

    close(client_sock);
    printf("\nConnection closed with client\n");

    close(server_sock);

    return 0;
}