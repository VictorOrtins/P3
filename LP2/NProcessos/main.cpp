#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/signal.h>

int main(int argc, char *argv[]){
    /*
        Bom dar uma revisada
    */
   
    int n{};
    std::cout << "Tel me the number of process you want to clone" << std::endl;
    std::cin >> n;
    
    std::vector<int> clone_pids{};

    int original_pid{getpid()};

    int ret_fork{};

    for (int i = 0; i < n; i++){
        if (original_pid == getpid()){
            ret_fork = fork();
            if (original_pid == getpid()){
                clone_pids.push_back(ret_fork);
            }
            else{
                std::cout << "[clone] em execução" << std::endl;
                sleep(60);
                break;
            }
        }
        else{
            std::cout << "[clone] em execução" << std::endl;
            sleep(60);
            break;
        }
    }

    if (original_pid == getpid()){
        std::cout << "Dormir por 10 segundos" << std::endl;
        sleep(10);
        std::cout << "Matando processo clonados..." << std::endl;
        for (int i = 0; i < n; i++){
            // std::cout << "Matando o processo: " << clone_pids.at(i) << std::endl;
            kill(clone_pids.at(i), SIGHUP); //O erro tava aqui:
            //Na função kill, sempre primeiro vem o PID do processo, depois vem o SIGHUP
        }
    }

    return 0;
}