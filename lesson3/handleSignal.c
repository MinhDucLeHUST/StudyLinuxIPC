#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "signal.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <bits/types/sigset_t.h>

#include "/usr/include/x86_64-linux-gnu/bits/sigaction.h"

int count_1 = 0;
int count_2 = 0;

void handleSignal(int number_of_signal);
void ignoreSignal(sigset_t new_set, sigset_t old_set);
void printSignal(sigset_t signal_set);

int main(int argc, char const *argv[]){
    /*Register SIGINT to handle*/
    sigset_t new_set, old_set;
    ignoreSignal(new_set, old_set);
    // signal(SIGCHLD, handleSignal); //catch SIGCHLD signal => return value of this signal => search by "kill -l" command on terminal
    /*Call systemCall kill() after 2s*/
    // sleep(2);
    // kill(getpid(),SIGINT);
    while(1);

    return 0;
}

void checkError (){
    if(signal(SIGINT, handleSignal) == SIG_ERR){
        fprintf(stderr, "Cannot handle signal SIGINT\n");
        exit(EXIT_FAILURE);
    }
}

void handleSignal(int number_of_signal){
    if(number_of_signal == 2){
        printf("Catch SIGINT: %d, counting: %d\n", number_of_signal, count_1++);
    }
    if(number_of_signal == 17){
        printf("Catch SIGCHLD: %d, counting: %d\n", number_of_signal, count_2++);
    }
}

void ignoreSignal(sigset_t new_set, sigset_t old_set){
    sigemptyset(&new_set);
    sigemptyset(&old_set);

    sigaddset(&new_set,SIGINT);
    // printf("new_set is: %lu\n", new_set);
    printSignal(new_set);
    if(sigprocmask(SIG_SETMASK, &new_set, &old_set) == 0){
        if(sigismember(&new_set, SIGINT) == 1){
            printf("SIGINT exist\n");
        }
        else{
            printf("SIGINT is not exist\n");
        }
    }
}

void printSignal(sigset_t signal_set){
    for (int signo = 1; signo < 32; signo++) {
        if (sigismember(&signal_set, signo)) {
            printf("Signal has number: %d was set\n", signo);
        }
    }
}