#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// const int MAX_CLIENTS = 10;
// const int BUFFER_SIZE = 1024;
// const int PORT = 9000;


#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define PORT 9000

#define SHUTDOWN_KEY "SHUTDOWN"
#define START_KEY "START"

// Struct para armazenar informações de cada cliente
typedef struct clientInfo{
  int socket;
  char name[BUFFER_SIZE];
}ClientInfo;

// Array de clientes
ClientInfo clients[MAX_CLIENTS];

// Buffer compartilhado
char buffer[BUFFER_SIZE];

// Variável para controlar o número de clientes conectados
int numClients = 0;

// Barreira para sincronizar a finalização do servidor
pthread_barrier_t shutdownBarrier;

// Função para tratar cada cliente em uma thread separada
void *clientHandler(void *arg) {
  ClientInfo *client = (ClientInfo *)arg;

  // Enviar string de início de conexão
  send(client->socket, START_KEY, strlen(START_KEY), 0);

    while (1) {
        // Receber string do cliente
        int bytesReceived = recv(client->socket, client->name, BUFFER_SIZE, 0);
        if (bytesReceived <= 0) {
            break;
        }

        // Adicionar string do cliente ao buffer compartilhado
        strcat(buffer, client->name);

        // Enviar buffer atualizado para todos os clientes
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].socket > 0) {
            send(clients[i].socket, buffer, strlen(buffer), 0);
            }
        }

        // Verificar se o cliente enviou a string "SHUTDOWN"
        if (strcmp(client->name, SHUTDOWN_KEY) == 0) {
            // Incrementar o contador de clientes que enviaram a string "SHUTDOWN"
            int *shutdownCounter = (int *)pthread_getspecific(0);
            (*shutdownCounter)++;
                // Verificar se o número mínimo de clientes enviou a string "SHUTDOWN"
            if (*shutdownCounter >= 4) {
                // Esperar pela finalização das threads de todos os clientes
                pthread_barrier_wait(&shutdownBarrier);

                // Finalizar servidor
                break;
            }
        }

    }
    // Fechar socket do cliente
    close(client->socket);

    // Limpar informações do cliente
    memset(client, 0, sizeof(*client));

    // Decrementar contador de clientes conectados
    numClients--;

    pthread_exit(NULL);
}

int main() {
    // Inicializar barreira para sincronizar a finalização do servidor
    pthread_barrier_init(&shutdownBarrier, NULL, MAX_CLIENTS + 1);

    // Criar socket do servidor
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        printf("Erro ao criar socket do servidor\n");
        return 1;
    }

    // Configurar endereço do servidor
    struct sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Vincular socket do servidor ao endereço
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Erro ao vincular socket do servidor\n");
        return 1;
    }

    // Iniciar escuta de conexões no socket do servidor
    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        printf("Erro ao iniciar escuta de conexões\n");
        return 1;
    }

    // Imprimir informações do servidor
    printf("Servidor iniciado na porta %d\n", PORT);

    while (1) {
        // Aceitar nova conexão
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            printf("Erro ao aceitar nova conexão\n");
            continue;
        }

        if (numClients >= MAX_CLIENTS){
            // Enviar mensagem de erro para o cliente
            send(clientSocket, "ERRO: limite de clientes atingido", strlen("ERRO: limite de clientes atingido"), 0);
              // Fechar socket do cliente
            close(clientSocket);
            continue;
        
        
        }
        // Incrementar contador de clientes conectados
        numClients++;

        // Encontrar posição vazia no array de clientes
        int i;
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].socket == 0) {
                break;
            }
        }

        // Armazenar informações do cliente
        clients[i].socket = clientSocket;


        // strcpy(clients[i].name, inet_ntoa(clientAddress.sin_addr));

        // Imprimir informações do cliente
        printf("Novo cliente conectado: %d", clients[i].socket);

        // Criar thread para tratar o cliente
        pthread_t thread;
        if (pthread_create(&thread, NULL, clientHandler, (void *)&clients[i]) != 0) {
            printf("Erro ao criar thread para tratar cliente\n");
            continue;
        }
    }
    // Fechar socket do servidor
    close(serverSocket);

    // Destruir barreira para sincronizar a finalização do servidor
    pthread_barrier_destroy(&shutdownBarrier);

    return 0;
}

