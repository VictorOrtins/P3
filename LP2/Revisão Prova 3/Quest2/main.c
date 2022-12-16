/*
Faça um programa em C/C++ que crie um servidor TCP que aguarde conexões na porta
9000. Este servidor deverá ser capaz de receber e tratar conexões de até 10 
clientes simultâneos. Cada nova conexão deverá receber uma string de início de 
conexão (ex. “START”). Faça o programa gerenciar um buffer compartilhado composto
por até 1024 caracteres. Este buffer deverá ser modificado concatenando cada nova
string recebida de cada um dos clientes. Sempre que receber uma nova string de um
dos clientes, o servidor modifica o buffer e o envia para todos os cliente.

Exemplo de execução:
	3 clientes se conectam;
	servidor envia “START” para os 3 clientes;
	cliente 1 envia a string “ABC” para o servidor;
	servidor envia buffer para o cliente 1: “ABC”;
	cliente 2 envia a string “XYZ” para o servidor;
	servidor envia buffer para cliente 2: “ABC\nXYZ”
	cliente 3 envia a string “IJK” para o servidor;
	servidor envia buffer para cliente 3: “ABC\nXYZ\nIJK”;

Se 4 dos clientes enviarem a string “SHUTDOWN” o servidor deverá ser 
finalizado. Utilize uma barreira para implementar esta funcionalidade.

O programa deverá utilizar a biblioteca POSIX Threads (PThreads) ou as threads
STD (C++11) e a biblioteca sockets.h (ou winsock.h). A saída do seu programa 
deve ser bem planejada, de forma a mostrar o que está acontecendo em cada 
momento relevante. Para testes do servidor, usar netcat (nc) ou telnet para 
o lado do cliente.
*/

/*
	O strcmp não tá querendo funcionar, creio que deva ser alguma coisa a ver com o
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
#include <strings.h>
#include <string.h>

#define MY_PORT 9997

#define QTD_CLIENTS 3

#define RECV_BUF_SIZE 32

pthread_barrier_t barrier;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int count_shutdown = 0;

void* client_handler(void* p) {
	int client_sock = (int)(long)p;
    char recv_buffer[RECV_BUF_SIZE] = "START\n";
    int s_ret;
    // s_ret = send(client_sock, recv_buffer, sizeof(recv_buffer), 0);

	while (1) {
		bzero(recv_buffer, RECV_BUF_SIZE);
		int r_ret = recv(client_sock, recv_buffer, sizeof(recv_buffer), 0);

	    printf("Recebi do cliente (%d): %s\n", client_sock, recv_buffer);
		printf("Ecoando mensagem...\n");
        
        if(strcmp(recv_buffer, "SHUTDOWN\n") == 0){
            pthread_mutex_lock(&mutex);
            count_shutdown++;
            pthread_mutex_unlock(&mutex);

            strcpy(recv_buffer, "Conexão Finalizada");
            s_ret = send(client_sock, recv_buffer, sizeof(recv_buffer), 0);
            pthread_exit(0);
        }

		s_ret = send(client_sock, recv_buffer, sizeof(recv_buffer), 0);

        // pthread_barrier_wait(&barrier);
	}
}

int main(void) {

    pthread_barrier_init(&barrier, NULL, QTD_CLIENTS + 1);

	struct sockaddr_in server_info;
	struct sockaddr_in client_info[QTD_CLIENTS];
	int client_info_len[QTD_CLIENTS];
	int client_counter = 0;

	int server_sock;
	int client_sock[QTD_CLIENTS];
	pthread_t client_threads[QTD_CLIENTS];

	printf("Servidor aguardando na porta: %d\n", MY_PORT);

	server_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (server_sock == -1) {
		printf("socket() error!\n");
		exit(0);
	}

	//informacoes do servidor
	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(MY_PORT);
	server_info.sin_addr.s_addr = INADDR_ANY; 

	//associo informacoes ao server socket 
	int b_ret = bind(server_sock, (struct sockaddr *)&server_info, sizeof(server_info));

	if (b_ret == -1) {
		printf("bind() error (%d)!\n", errno);
		exit(0);
	}

	//notifico SO - server socket
	int l_ret = listen(server_sock, QTD_CLIENTS);

	if (l_ret == -1) {
		printf("listen() error (%d)!\n", errno);
		exit(0);
	}

	//aguarda novas conexoes 
	
	while (1) {	
		client_sock[client_counter] = accept(server_sock, (struct sockaddr *)&client_info[client_counter], &client_info_len[client_counter]);

		//conexao recebida - estrutura com info
		//do cliente populada

		char* str_addr = inet_ntoa(client_info[client_counter].sin_addr);

		printf("Recebi uma conexao!\n");
		printf("Endereco: %s\n", str_addr);

		if (client_sock[client_counter] == -1) {
			printf("accept() error (%d)!", errno);
			exit(0);
		}

		pthread_create(&client_threads[client_counter], 0,client_handler,(void*)(long)client_sock[client_counter]);

        printf("%d", count_shutdown);
        pthread_mutex_lock(&mutex);
        if(count_shutdown == 4){
            printf("Desconectando servidor\n");
            break;
        }
        pthread_mutex_unlock(&mutex);

		client_counter++;
	}

	//fecha recepcao de novas conexoes
	close(server_sock);

	return 0;
}

