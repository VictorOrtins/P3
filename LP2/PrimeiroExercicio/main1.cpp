#include <iostream>
#include <string>
using namespace std;


int main(int argc, char *argv[]){
    int loop_number{stoi(argv[1])};

    for (int i = 0; i < loop_number; i++){
        cout << "Hello from C++ on Ubuntu on Windows" << endl;
    }

    return 0;
}