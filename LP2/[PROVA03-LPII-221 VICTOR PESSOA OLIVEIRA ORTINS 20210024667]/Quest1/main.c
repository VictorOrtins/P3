/*
(Questão 1 - 8 pontos) Faça um programa em C/C++ que implemente um servidor
que atenda os requisitos listados a seguir.
 
	1) Receba até 10 conexões simultâneas de clientes na porta 9622 TCP;
 
	2) Cada cliente deve enviar uma string ao se conectar ao servidor: 
	"START" para que a comunicação seja iniciada. Caso o cliente envie
	outra string, a conexão com ele deverá ser finalizada.
 
	3) O servidor tratará strings enviadas pelos clientes como comandos, e 
	retornára o resultado como descrito a seguir. Os seguintes comandos
	devem ser suportados: 
 
		a) CRTIME\n fará o servidor retornar a data e hora corrente;
 
		b) RNDNUM\n o servidor irá gerar e retornar um valor aleatório 
		entre 0 e 100;
 
		c) FINISH\n fará o servidor finalizar a conexão com o cliente;
 
		d) SHTDWN\n envia mensagem para todos os clientes informando 
		que o servidor será finalizado; finaliza o processo do servidor;
 
		e) Comandos não reconhecidos deverão fazer o servidor retornar
		"ERROR" para os clientes.
 
Comente o código explicando a diferença entre os papéis de cliente e servidor, 
ressaltando quais chamadas feitas no código são necessárias no contexto 
específico do protocolo TCP. Teste o servidor com múltiplos clientes, usando
instâncias de telnet ou nc (netcat). Explique também as diferenças com relação
ao uso de sockets com TCP e UDP.
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

/*

    O servidor é quem aguarda as solicitações do cliente, e o cliente é quem faz essas solicitações.
    O servidor é, então, uma espécie de host que compartilha os recursos necessários e solicitados para o cliente.
    Este, portanto, não compartilha recursos com o servidor, apenas de fato solicita recursos do servidor.
    No caso do servidor TCP, é necessária a chamada das funções:

    socket(), que cria o socket do servidor.
    bind(), que é obrigatória no caso do servidor, porém opcional para p cliente.
    listen() que notifica ao servidor a utilização da porta desejada.
    accept(), que aceita a conexão com o cliente.
    close(), para fechar o servidor.

    No caso do cliente TCP, é necessária a chamada das funções:
    socket(), que cria o socket do cliente.
    connect(), para formar a conexão virtual com o servidor.
    close(), para fechar o cliente.

    A diferença do uso de sockets em TCP e UDP é bem nítida. Após a criação do socket, no caso do TCP,
    é necessária a existência de uma conexão, que funciona quase que como um circuito virtual entre o cliente e o servidor.
    No caso do UDP, essa conexão não existe, ou seja, a função accept no servidor TCP e a conect no cliente TCP são
    exclusivas desse tipo de servidor. No caso do servidor TCP, é necessário também a utilização
    da função listen. Explicando de forma mais teórica, agora, o TCP, além de criar a conexão virtual que mencionei antes,
    também garante entrega e ordem de entrega, que o UDP não garante. Então, no TCP, o modelo cliente/servidor
    é explícito, sabemos quem é o cliente e quem é o servidor pela diferença das chamadas das funções. No caso do UDP,
    o modelo não é tão explícito, já que apenas a ordem da chamada das funções que diferencia o cliente e o servidor.
*/

//9622

#define SERVER_PORT 9622
#define QTD_CLIENTS 10
#define RECV_BUFFER_SIZE 60

int server_sock;
long clients_sock[QTD_CLIENTS];
pthread_mutex_t mutex;

void* thread_func(void* p);

int main(void){
    pthread_mutex_init(&mutex, 0); //Inicializador do mutex da seção crítica das threads
    struct sockaddr_in server; //servidor
    struct sockaddr_in clients[QTD_CLIENTS]; //clientes

    int clients_len[QTD_CLIENTS];

    pthread_t threads[QTD_CLIENTS]; //Threads que tratam os clientes

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    server_sock = socket(AF_INET, SOCK_STREAM, 0); //Criação do socket do servidor
    if(server_sock < 0){
        printf("Erro ao criar o socket do servidor (%d)\n", errno);
        exit(-1);
    }

    if(bind(server_sock, (struct sockaddr*)&server, sizeof(server)) < 0){ //Bind do servidor
        printf("Erro no bind (%d)\n", errno);
        exit(-1);
    } //Não é específico do TCP, porém é opcional no servidor UDP

    if(listen(server_sock, QTD_CLIENTS) < 0){ //Listen do servidor
        printf("Erro no listen (%d)\n", errno);
        exit(-1);
    } //Específico do TCP

    int client_counter = 0; //Contador de clientes

    printf("Servidor criado na porta %d!\n", SERVER_PORT);
    while(1){
        clients_sock[client_counter] = accept(server_sock, (struct sockaddr*)&clients[client_counter], &clients_len[client_counter]);
        //Específico do TCP

        printf("Recebi uma conexão do cliente %d!\n\n", client_counter + 1);

        if(clients_sock[client_counter] < 0){
            printf("Erro ao estabelecer a conexão\n");
            exit(-1);
        }

        pthread_create(&threads[client_counter], 0, thread_func, (void*)clients_sock[client_counter]); //Criação da thread que vai lidar com o cliente que acabou de conectar-se
        client_counter++;
    }


    close(server_sock);

    return 0;
}

void* thread_func(void* p){
    long client_sock = (long)p;
    char recv_buffer[RECV_BUFFER_SIZE]; //recv_buffer é local, então não precisa de mutex nele

    time_t t;
    srand(time(&t)); //seed do random

    int valor_aleatorio;

    strcpy(recv_buffer, "Digite START para iniciar\n");
    send(client_sock, recv_buffer, sizeof(recv_buffer), 0);

    bzero(recv_buffer, RECV_BUFFER_SIZE);
    recv(client_sock, recv_buffer, sizeof(recv_buffer), 0);

    if(strncmp(recv_buffer, "START", 5) != 0){ //Confirmando se cliente digitou START para a conexão iniciar. Se não, conexão será finalizada
        bzero(recv_buffer, RECV_BUFFER_SIZE);

        strcpy(recv_buffer, "Conexão inválida\n");
        send(client_sock, recv_buffer, sizeof(recv_buffer), 0);
        printf("Fechando conexão com o cliente %ld\n", client_sock);
        close(client_sock); //Finalizando conexão
        pthread_exit(0);
    }


    send(client_sock, "BEM-VINDO\n", 10, 0); //Mensagem de boas-vindas
    while(1){
        time(&t);
        struct tm *hora_sistema;
        hora_sistema = localtime(&t);

        bzero(recv_buffer, RECV_BUFFER_SIZE);
        recv(client_sock, recv_buffer, sizeof(recv_buffer), 0);

        printf("Recebi do cliente %ld: %s\n", client_sock, recv_buffer);
        if(strncmp(recv_buffer, "RNDNUM", 6) == 0){ 

            bzero(recv_buffer, RECV_BUFFER_SIZE);

            valor_aleatorio = rand() % 100; //Gerando número aleatório e enviando para o cliente
            sprintf(recv_buffer, "%d\n", valor_aleatorio);

            printf("Valor enviado para cliente %ld: %d\n\n", client_sock, valor_aleatorio);
            send(client_sock, recv_buffer, sizeof(recv_buffer), 0); //Enviando número para o cliente            
        }
        else if(strncmp(recv_buffer, "CRTIME", 6) == 0){

            bzero(recv_buffer, RECV_BUFFER_SIZE);

            sprintf(recv_buffer, "%d/%d/%d %d:%d:%d\n", hora_sistema->tm_mday, hora_sistema->tm_mon + 1, hora_sistema->tm_year + 1900, hora_sistema->tm_hour, hora_sistema->tm_min, hora_sistema->tm_sec);
            //Coletando a hora do sistema
            printf("Hora do sistema enviado para o cliente %ld\n", client_sock);
            send(client_sock, recv_buffer, sizeof(recv_buffer), 0); //Enviando a hora do sistema para o cliente
        }
        else if(strncmp(recv_buffer, "FINISH", 6) == 0){

            bzero(recv_buffer, RECV_BUFFER_SIZE);
            strcpy(recv_buffer, "Finalizando conexão\n");
            send(client_sock, recv_buffer, sizeof(recv_buffer), 0); //Enviando mensagem de conexão finalizada

            printf("Finalizando conexão com cliente %ld\n", client_sock);
            close(client_sock); //Fechando socket
            break;
        }else if(strncmp(recv_buffer, "SHTDWN", 6) == 0){
            bzero(recv_buffer, RECV_BUFFER_SIZE);
            strcpy(recv_buffer, "Servidor Finalizado\n");

            pthread_mutex_lock(&mutex); //Variáveis clients_socks e server_socks são globais, então é necessário que só uma thread mexa nelas
            printf("SHTDWN recebido\nFinalizando Servidor\n");

            send(client_sock, recv_buffer, sizeof(recv_buffer), 0); //Enviando para o cliente a msg de que o servidor fechou
            for(int i = 0; i < QTD_CLIENTS; i++){
                send(clients_sock[i], recv_buffer, sizeof(recv_buffer), 0); //E agora para todos os outros clientes
            }

            for(int i = 0; i < QTD_CLIENTS; i++){
                close(clients_sock[i]); //Fechando todas as conexões com os clientes
            }

            close(server_sock); //Fechando conexão do servidor
            pthread_mutex_unlock(&mutex);
            exit(0);
        }
        else{
            send(client_sock, "ERROR\n", sizeof("ERROR\n"), 0); //Enviando mensagem de erro
            printf("Comando inválido\n");
            continue;
        }
    }
}