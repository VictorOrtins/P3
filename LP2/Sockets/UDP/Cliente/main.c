#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>

#define SIZE_BUFFER 32

#define SERVER_PORT 9998
#define CLIENT_PORT 9999

int main(void){

    char *ip = "127.0.0.1"; 
    char recv_buffer[SIZE_BUFFER];

    struct sockaddr_in client;
    struct sockaddr_in server;

    socklen_t client_size, server_size;

    int server_sock, client_sock;

    client_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_sock < 0){
        printf("Error while creating socket %d", errno);
        exit(1);
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(SERVER_PORT);
    client.sin_addr.s_addr = inet_addr(ip);

    bzero(recv_buffer, SIZE_BUFFER);
    strcpy(recv_buffer, "Hello, World!");
    sendto(client_sock, recv_buffer, SIZE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
    printf("Data sent: %s\n", recv_buffer);

    server_sock = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_port = htons(SERVER_PORT);

    server_size = sizeof(server);

    bzero(recv_buffer, SIZE_BUFFER);
    client_size = sizeof(client);
    recvfrom(client_sock, recv_buffer, SIZE_BUFFER, 0, (struct sockaddr*)&server, &server_size);
    printf("Data received: %s\n", recv_buffer);

  

    

    return 0;
}
