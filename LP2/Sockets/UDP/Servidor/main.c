#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define SIZE_BUFFER 32

#define SERVER_PORT 9998
#define CLIENT_PORT 9999

int main(void){

    char *ip = "127.0.0.1"; 
    char recv_buffer[SIZE_BUFFER];

    struct sockaddr_in server;
    struct sockaddr_in client;

    int server_sock, client_sock;
    socklen_t client_size;

    server_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_sock < 0){
        printf("Error while creating socket %d", errno);
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(ip);

    if(bind(server_sock, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Bind error %d", errno);
        exit(1);
    }

    bzero(recv_buffer, SIZE_BUFFER);
    client_size = sizeof(client);
    recvfrom(server_sock, recv_buffer, SIZE_BUFFER, 0, (struct sockaddr*)&client, &client_size);
    printf("Data received: %s\n", recv_buffer);

    client_sock = socket(AF_INET, SOCK_DGRAM, 0);
    client.sin_port = htons(SERVER_PORT);

    bzero(recv_buffer, SIZE_BUFFER);
    strcpy(recv_buffer, "Welcome to the UDP Server!");
    sendto(server_sock, recv_buffer, SIZE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
    printf("Data sent: %s\n", recv_buffer);





    return 0;
}
