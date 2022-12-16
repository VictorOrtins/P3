#include <stdio.h>
#include <vector>

using namespace std;

int main(void)
{
    int numero_de_regioes, m_a_testar;

    scanf("%d", &numero_de_regioes);

    while(numero_de_regioes > 0)
    {
        m_a_testar = 1;
        int posicao = 0;

        vector<int> regioes;

        for(int i = 1; i <= numero_de_regioes; i++){
            regioes.push_back(i);
        }


        while(true){

            do{
                regioes.erase(regioes.begin() + posicao);
                posicao = (posicao - 1 + m_a_testar) % regioes.size();
            }while(regioes.size() > 1);


            if(regioes.at(0) == 13){
                break;
            }
            
            m_a_testar++;
            regioes.clear();
            for(int i = 1; i <= numero_de_regioes; i++){
                regioes.push_back(i);
            }
        }

        printf("%d\n", m_a_testar);
        scanf("%d", &numero_de_regioes);
    }
    return 0;
}