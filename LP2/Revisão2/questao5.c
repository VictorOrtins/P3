// /*
// (Questão 5) Faça um programa em C/C++ onde são criadas 2 threads: uma thread produtora, e a outra consumidora. 
// A thread produtora deverá gerar 100 valores inteiros aleatórios entre 0 e 255 e armazenar em um 
// array compartilhado com 10 posições.
// A thread consumidora buscará as informações no array e exibi-los, de forma que nenhum valor seja perdido. 
// Use semáforos implementando a solução do buffer compartilhado. 
// */

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <time.h>
// #include <unistd.h>

// #define QTD_BUF 10

// sem_t buf_empty, buf_full;
// int rear = 0, front = 0;
// int buf[QTD_BUF];


// void* produtor(void* p){
//     long id = (long)p;
//     int random;
//     int contador = 0;

//     while(contador < 100){
//         sem_wait(&buf_empty);
//         random = rand() % 255;
//         buf[rear] = random;
//         printf("[Thread %ld] Gerou %d e depositou no slot %d\n", id, random, rear);
//         rear = (rear + 1) % QTD_BUF;
//         sem_post(&buf_full);
//         // sleep(1);
//         contador++;
//     }
// }

// void* consumidor(void* p){
//     long id = (long)p;
//     int contador = 0;
//     int temp;

//     while(contador < 100){
//         sem_wait(&buf_full);
//         temp = buf[front];
//         printf("[Thread %ld] Consumiu %d do slot %d\n", id, temp, front);
//         front = (front + 1) % QTD_BUF;
//         sem_post(&buf_empty);
//         // sleep(1);
//         contador++;
//     }
// }


// int main(void){
//     pthread_t prod, cons;
//     time_t t;

//     srand(time(&t));

//     sem_init(&buf_empty, 0, QTD_BUF);
//     sem_init(&buf_full, 0, 0);

//     pthread_create(&prod, 0, produtor, (void*)0);
//     pthread_create(&cons, 0, consumidor, (void*)1);

//     pthread_join(prod, 0);
//     pthread_join(cons, 0);


//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define TAM_BUF 10

int buf[TAM_BUF];
sem_t buf_empty, buf_full;
int rear = 0, front = 0;

void* producer(void* p) {
	int data;
	int count = 0;
	while(count < 100) {
		sem_wait(&buf_empty);
		data = rand() % 100;
		buf[rear] = data;
		printf("[prod] gerou %d e depositou no slot %d (%d)\n", 
				data,rear, count);
		rear = (rear + 1) % TAM_BUF;
		//sleep(1);
		sem_post(&buf_full);
		count++;
	}
}

void* consumer(void* p) {
	int result;
	int count = 0;
	while(count < 100) {
		sem_wait(&buf_full);
		result = buf[front];
		printf("[cons] consumiu %d do slot %d (%d)\n",
			       	result, front, count);
		front = (front + 1) % TAM_BUF;
		//sleep(1);
		sem_post(&buf_empty);
		count++;
	}

}

int main(void) {
	time_t t;
	pthread_t prod;
	pthread_t cons;

	srand(time(&t));

	sem_init(&buf_empty, 0, TAM_BUF);
	sem_init(&buf_full, 0, 0);

	pthread_create(&prod, 0, producer, (void*)0);

	pthread_create(&cons, 0, consumer, (void*)0);

	pthread_join(prod, 0);
	pthread_join(cons, 0);

	return 0;
}





