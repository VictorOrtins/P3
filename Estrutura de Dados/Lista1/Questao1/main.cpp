#include <iostream>
#include <string>
 
using namespace std;
const int NULL_VALUE{-1024};

void print_array(long int array[], int length, bool par){
    string array_name{};
    if (par){
        array_name = "par";
    }
    else{
        array_name = "impar";
    }

    for(int i = 0; i < length; i++){
        // if (array[i] ==  NULL_VALUE){
        //     break;
        // }

        cout << array_name + "[" << i << "] = " << array[i] << endl;
    }
}
 
int main() {

    const int VALORES_A_LER{15};
    const int ARRAY_SIZE{5};
 
    long int pares[ARRAY_SIZE]{};
    long int impares[ARRAY_SIZE]{};
    int temp_var{};

    int pares_length{0};
    int impares_length{0};

    for (int i = 0; i < VALORES_A_LER; i++){
        cin >> temp_var;

        if (temp_var % 2 == 0){
            pares[pares_length] = temp_var;
            pares_length++;
        }
        else{
            impares[impares_length] = temp_var;
            impares_length++;
        }
            
        if(pares_length == 5){
            print_array(pares, pares_length, true);

            for(int i = 0; i < 5; i++){
                pares[i] = NULL_VALUE;
            }

            pares_length = 0;
        }

        if (impares_length == 5){
            print_array(impares, impares_length, false);

            for(int i = 0; i < 5; i++){
                impares[i] = NULL_VALUE;
            }

            impares_length = 0;
        }
    }

    print_array(impares, impares_length, false);
    print_array(pares, pares_length, true);

    return 0;
}