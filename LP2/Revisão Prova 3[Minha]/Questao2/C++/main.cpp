#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>

using namespace std;

typedef struct{
	int operacao;
	char codigo;
	float valor;
}operacao_bancaria;

class Monitor{
    private:
        static mutex lock;
        static ofstream file;
    public:
        Monitor(){
            file.open("arquivo.bin");
        }

        static void thread_func(operacao_bancaria op){
            lock.lock();
            file << op.codigo << op.operacao << op.valor << endl;
            lock.unlock();
        }
};

int main(void){
    const int QTD_OPERACOES = 5;

    operacao_bancaria operacoes[QTD_OPERACOES];

    for(int i = 0; i < QTD_OPERACOES; i++){
        operacoes[i].codigo = 'A' + rand() % 26;
        operacoes[i].operacao = rand() % 5;
        operacoes[i].valor = (rand() % 150) + 25;
    }

    Monitor monitor;

    thread t1(Monitor::thread_func, monitor, operacoes[0]);
    thread t2(Monitor::thread_func, monitor, operacoes[1]);
    thread t3(Monitor::thread_func, monitor, operacoes[2]);
    thread t4(Monitor::thread_func, monitor, operacoes[3]);
    thread t5(Monitor::thread_func, monitor, operacoes[4]);


    return 0;
}