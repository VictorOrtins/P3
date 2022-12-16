#include <stdio.h>
#include <vector>

using std::vector;

int main(){
    const int MAX{1000};

    vector <int> G[MAX];

    int array_length, consultas, consulta, valor, array_value;

    while(scanf("%d %d", &array_length, &consultas) != EOF){
        for(int i = 1; i <= MAX; i++)
            G[i].clear();
        for(int i = 1; i <= array_length; i++){
            scanf("%d", &array_value);
            G[array_value].push_back(i);
        }
        for(int i = 1; i <= consultas; i++){
            scanf("%d %d", &consulta, &valor);
            consulta--;
            if(consulta >= G[valor].size())
                printf("0\n");
            else
                printf("%d\n", G[valor][consulta]);
        }
    }
    return 0;
}