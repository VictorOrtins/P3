#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(void){

    int array_length{0};
    int number_of_searches{};

    // cin >> array_length >> number_of_searches;

    int array[array_length];
    int temp{};

    int instance{0},value{0}, counter{0}, position{0};

    while(cin >> array_length >> number_of_searches){
        for(int i = 0; i < array_length; i++){
            cin >> temp;
            array[i] = temp;
        }

        for (int i = 0; i < number_of_searches; i++){
            cin >> instance >> value;
            for (int j = 0; j < array_length; j++){
                if (array[j] == value){
                    counter++;
                    if (counter == instance){
                        break;
                    }
                }
                position++;
            }

            
            if (position == array_length){
                cout << 0 << endl;
            }
            else{
                cout << position + 1 << endl;
            }

            counter = 0;
            position = 0;   
        }

    }

    return 0;
}