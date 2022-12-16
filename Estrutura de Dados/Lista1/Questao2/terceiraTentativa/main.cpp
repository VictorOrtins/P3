#include <iostream>
#include <vector>

using std::cout;
using std::vector;
using std::endl;

#define MAX 1000

int main(void){

    vector<int> array_of_arrays[MAX]{};

    int array_length{};
    int consultas{};
    int temp{};
    int num_consultas{0};

    int instancia{0};
    int valor{0};
    int cont_instancia{0};

    while(scanf("%d %d", &array_length, &consultas) != EOF){
        for(int i = 0; i < MAX; i++){
            array_of_arrays[i].clear();
        }
        
        for(int i = 0; i < array_length; i++){
            scanf("%d", &temp);
            array_of_arrays[num_consultas].push_back(temp);
            // cout << "teste" << endl;
        }

        for(int i = 0; i < consultas; i++){
            scanf("%d %d", &instancia, &valor);
            for(int j = 0; j < array_length; j++){
                if(array_of_arrays[num_consultas].at(j) == valor){
                    cont_instancia++;
                    if(cont_instancia == instancia){
                        cout << cont_instancia << endl;
                        break;
                    }
                }
            }

            if(cont_instancia == array_length){
                cout << 0 << endl;
            }

            cont_instancia = 0;
            num_consultas++;
        }
    }

    return 0;
}
