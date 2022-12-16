#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    int loop_number{stoi(argv[1])};
    string string_temp{};
    for (int i = 0; i < loop_number; i++){
        getline(cin,string_temp);
        cout << "Prog 2: " << string_temp << endl;
    }

    return 0;
}

