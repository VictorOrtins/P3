/*
Faça um programa em C/C++ que contenha um monitor que controle o acesso de escrita
e leitura de um arquivo binário, que armazena itens de acordo com a struct descrita abaixo: 

typedef struct {
	int operacao;
	char codigo;
	float valor;
} operacao_bancaria;

Faça a função principal instanciar este monitor e crie 5 threads para que estas
façam operações de escria e leitura no arquivo.
*/



#include <stdio.h>
#include <pthread.h>

class Monitor{
	private:
		pthread_mutex_t lock;
		FILE *arq;
	
	public:
		Monitor(){
			pthread_mutex_init(&lock, 0);

			pthread_mutex_lock(&lock);
			arq = fopen("teste.txt", "w");
			arq = fopen("teste.txt", "r");
			pthread_mutex_unlock(&lock);
		}


};

int main(void){

}


