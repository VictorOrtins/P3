#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>
#include <pthread.h>
#include <time.h>

#define QTD_THREADS 10

int number = 1, next = 1; //Inicializando a variável do ticket e do next
int global = 0;
int turn[QTD_THREADS]; //Tíquetes correspondentes

/*
    RESPOSTA TEÓRICA:

    A propriedade de safety é cumprida dado que não existem deadlocks. A variável next sempre é igual
    a turn[id] na primeira thread escalonada e esta variável next sempre é incrementada quado a thread sai
    da seção crítica. O ticket recebido pelas threads também sempre é incrementado quando entre no while. Logo,
    sempre que uma das threads chegar em while(turn[id] != next), em algum momento essa condição não será cum-
    prida e a thread entrará na seção crítica.

    A exclusão mútua é sempre cumprida já que a variável next sempre é incrementada ao sair da seção crítica.
    Ou seja, sempre que uma thread recebe um ticket, ela checa se esse ticket for igual a next. Se não for, a
    thread fica na espera ocupada. Se for, entra na seção crítica. Caso o escalonador escalonar outra thread 
    enquanto ela estiver na seção crítica, é certeza que o valor de turn[id] dessa outra thread será diferente
    de next, já que os tickets de cada thread são sempre diferentes e o next não se alterou.

    Há ausência de atraso desnecessário nesse código, visto que a espera ocupada sempre é "finalizada" (ou seja,
    turn[id] == next nesses casos) quando não há nenhuma thread na seção crítica e há outra querendo entrar

    Eventualmente, todas as threads acessarão a seção crítica, tendo em vista que o incremento de number "para"
    quando N - 1 threads estão na espera ocupada e next sempre é incrementado quando uma thread sai da seção crítica.
    Então, em algum momento, o incremento de next vai chegar exatamente igual ao número em turn[N], assim, todas
    as threads terão o momento em que turn[id] == next, e isso garante a execução da seção crítica por todas as
    threads.

*/

void* thread_func(void* p){
    long id = (long)p;

    //Variáveis necessárias para pegar o tempo do sistema
    time_t segundos;
    struct tm *tempo_sistema;

    int contador = 0; //contador de vezes que a thread entrou na seção crítica
    while(contador < 50){
        turn[id] = atomic_fetch_add(&number, 1); //Dando o ticket correspondente a thread e incrementando number de forma atômica
        printf("[%ld] checando se turn[id] == next\n", id);
        while(turn[id] != next){ //Espera ocupada das threads que não devem entrar na seção crítica
            // printf("[%ld] estou na espera ocupada\n", id);
        }

        //Seção crítica
        time(&segundos);
        tempo_sistema = localtime(&segundos); //Struct que dá o tempo do sistema
        printf("[%ld] entrou na secao critica as %d:%d:%d do dia %d/%d/%d\n", id, tempo_sistema->tm_hour, tempo_sistema->tm_min, tempo_sistema->tm_sec, tempo_sistema->tm_mday, tempo_sistema->tm_mon + 1, tempo_sistema->tm_year + 1900);
        global++;
        atomic_fetch_add(&next, 1); //Incrementando a variável next para que o próximo ticket esteja atualizado de forma correta
        //Saindo da seção crítica
        printf("[%ld] saiu da secao critica\n", id);
        contador++;
    }
}

int main(void){

    pthread_t threads[QTD_THREADS]; //Array de threads

    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, thread_func, (void*)i); //Criando threads
    }

    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], NULL); //Juntando as threads para que todas executem todo o código eventualmente
    }

    printf("[main] global = %d\n", global); //Valor da variável global após todas as iterações

    return 0;
}