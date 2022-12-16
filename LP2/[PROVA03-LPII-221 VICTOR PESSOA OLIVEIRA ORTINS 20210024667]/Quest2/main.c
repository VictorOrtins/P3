/*
(Questão 2 - 4 pontos) Faça um monitor que controle o acesso de escrita e 
leitura em um arquivo de texto; modifique o código da questão anterior 
para que todos os comandos enviados pelos clientes sejam registrados em um
arquivo de texto cujo acesso é controlado pelo novo monitor implementado.
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

typedef struct{
    FILE* arq;
    pthread_mutex_t lock;
}Monitor;

Monitor monitor;

//9622
#define SERVER_PORT 9622
#define QTD_CLIENTS 10
#define RECV_BUFFER_SIZE 60
#define TEMP_BUFFER_SIZE 100
#define FILENAME "log.txt"

int server_sock;
long clients_sock[QTD_CLIENTS];
pthread_mutex_t mutex;

void* thread_func(void* p);
void construtor_monitor();
void write_file(char* str, size_t size);

int main(void){
    construtor_monitor();
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

        printf("Recebi uma conexão\n\n");

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

void construtor_monitor(){
    pthread_mutex_init(&monitor.lock, 0);
    monitor.arq = fopen(FILENAME, "w");
}

void write_file(char* str, size_t str_size){ //Função que trata a escrita do arquivo
    pthread_mutex_lock(&monitor.lock); //Lock do monitor
    fputs(str, monitor.arq); //Escrevendo no arquivo contido no monitor
    pthread_mutex_unlock(&monitor.lock); //Unlock do monitor
}

void* thread_func(void* p){
    long client_sock = (long)p;
    char recv_buffer[RECV_BUFFER_SIZE]; //recv_buffer é local, então não precisa de mutex nele
    char temp[TEMP_BUFFER_SIZE];

    time_t t;
    srand(time(&t)); //seed do random

    int valor_aleatorio;

    strcpy(recv_buffer, "Digite START para iniciar\n");
    send(client_sock, recv_buffer, sizeof(recv_buffer), 0);

    bzero(recv_buffer, RECV_BUFFER_SIZE);
    recv(client_sock, recv_buffer, sizeof(recv_buffer), 0);

    bzero(temp, TEMP_BUFFER_SIZE);
    sprintf(temp, "%s", recv_buffer);
    write_file(temp, TEMP_BUFFER_SIZE);


    if(strncmp(recv_buffer, "START", 5) != 0){ //Confirmando se cliente digitou START para a conexão iniciar. Se não, conexão será finalizada
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

        bzero(recv_buffer, RECV_BUFFER_SIZE); //Reiniciando buffer
        recv(client_sock, recv_buffer, sizeof(recv_buffer), 0); //Recebido co cliente indo pro buffer

        printf("Recebi do cliente: %s\n", recv_buffer);

        bzero(temp, TEMP_BUFFER_SIZE);
        sprintf(temp, "%s",recv_buffer);
        write_file(temp, TEMP_BUFFER_SIZE);
        if(strncmp(recv_buffer, "RNDNUM", 6) == 0){ 

            bzero(recv_buffer, RECV_BUFFER_SIZE);

            valor_aleatorio = rand() % 100; //Gerando número aleatório e enviando para o cliente
            sprintf(recv_buffer, "%d\n", valor_aleatorio);

            printf("Valor enviado para cliente: %d\n\n", valor_aleatorio);
            send(client_sock, recv_buffer, sizeof(recv_buffer), 0); //Enviando número para o cliente            
        }
        else if(strncmp(recv_buffer, "CRTIME", 6) == 0){

            bzero(recv_buffer, RECV_BUFFER_SIZE);

            sprintf(recv_buffer, "%d/%d/%d %d:%d:%d\n", hora_sistema->tm_mday, hora_sistema->tm_mon + 1, hora_sistema->tm_year + 1900, hora_sistema->tm_hour, hora_sistema->tm_min, hora_sistema->tm_sec);
            //Coletando a hora do sistema
            printf("Hora do sistema enviado para o cliente\n");
            send(client_sock, recv_buffer, sizeof(recv_buffer), 0); //Enviando a hora do sistema para o cliente
        }
        else if(strncmp(recv_buffer, "FINISH", 6) == 0){

            bzero(recv_buffer, RECV_BUFFER_SIZE);
            strcpy(recv_buffer, "Finalizando conexão\n");
            send(client_sock, recv_buffer, sizeof(recv_buffer), 0); //Enviando mensagem de conexão finalizada

            printf("Finalizando conexão com cliente\n");
            close(client_sock); //Fechando socket
            break;
        }else if(strncmp(recv_buffer, "SHTDWN", 6) == 0){


            pthread_mutex_lock(&mutex); //Variáveis clients_socks e server_socks são globais, então é necessário que só uma thread mexa nelas
            bzero(recv_buffer, RECV_BUFFER_SIZE);
            strcpy(recv_buffer, "Servidor Finalizado\n");
            printf("SHTDWN recebido\nFinalizando Servidor\n");

            for(int i = 0; i < QTD_CLIENTS; i++){
                send(clients_sock[i], recv_buffer, sizeof(recv_buffer), 0); //Enviando msg para todos os outros clientes
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