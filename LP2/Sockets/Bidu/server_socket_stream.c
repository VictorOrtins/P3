#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MY_PORT 9999

int main(void) {
	unsigned short port;
	char recv_buffer[32];
	struct sockaddr_in server_info;
	struct sockaddr_in client_info;
	int client_len;

	int server_sock;
	int client_sock;

	printf("Servidor aguardando na porta: %d\n", 
			MY_PORT);

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
	int b_ret = bind(server_sock, 
			(struct sockaddr *)&server_info,
			sizeof(server_info));

	if (b_ret == -1) {
		printf("bind() error (%d)!\n", errno);
		exit(0);
	}

	//notifico SO - server socket
	int l_ret = listen(server_sock, 3);

	if (l_ret == -1) {
		printf("listen() error (%d)!\n", errno);
		exit(0);
	}

	//aguarda novas conexoes 
	client_sock = accept(server_sock, 
			(struct sockaddr *)&client_info,
			&client_len);

	//conexao recebida - estrutura com info
	//do cliente populada
	char* str_addr = 
		inet_ntoa(client_info.sin_addr);

	printf("Recebi uma conexao!\n");
	printf("Endereco: %s\n", str_addr);

	if (client_sock == -1) {
		printf("accept() error (%d)!", errno);
		exit(0);
	}

	//envio e recepcao de informacoes 
	//(cliente conectado)
	char send_buf[12] = "Bem vindo!\n";

	printf("Enviando para o cliente: %s\n",
				send_buf);

	int s_ret = send(client_sock, send_buf, 
			sizeof(send_buf), 0);

	if (s_ret == -1) {
		printf("send() error (%d)!\n",errno);
	}

	int r_ret = recv(client_sock, recv_buffer,
			sizeof(recv_buffer), 0);

	printf("Recebi do cliente: %s\n", recv_buffer);


	//fecha conexao com cliente
	close(client_sock);

	//fecha recepcao de novas conexoes
	close(server_sock);

	return 0;
}
