#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"
#include "sys/types.h"
#include "signal.h"

void createProcess (__pid_t child_pid);
void usingWaitToKillProcess (__pid_t child_pid);
void func(int signal_number);
void usingSignal(__pid_t child_pid);

int main(int argc, char const *argv[]){
    //define child process
    __pid_t child_pid;
    // usingWaitToKillProcess(child_pid);
    usingSignal(child_pid);

    return 0;
}

//ex1: Fundamental about process => how to create a child process
void createProcess (__pid_t child_pid){
    int count = 0;

    printf("Value of count = %d\n", count);
    child_pid = fork(); //create child process
    if(0 == child_pid){// valid value of child_pid just only = 0
        // count ++;
        printf("Child process, value of count = %d\n", ++count);
        printf("Child process 's PID = %d, Parent's PID of child_pid = %d\n", getpid(), getppid());
    }else{  // 1st run
        count +=2;
        printf("Parent process, value of count = %d\n", count);
        printf("Parent process 's PID = %d\n", getpid());
        while(1);
    }
}

//ex2: Function using system call wait
void usingWaitToKillProcess (__pid_t child_pid){
    int return_value;
    int status;
    child_pid = fork();
    if(0 == child_pid){
        printf("Child process 's PID = %d\n", getpid());
        printf("Child process will be killed after 5s ...\n");
        sleep(5);
        // while(1); // create to check value of signal when using WTERMSIG(status)
        exit(0);
    }
    else{
        return_value = wait(&status);
        if(return_value == -1){
            printf("system call wait() can't using => unsuccessful!\n");
        }
        printf("Parent process, PID = %d\n\n", return_value);

        if(WIFEXITED(status)){
            printf("Ending normally, status = %d\n", WEXITSTATUS(status));
        }
        else{
            printf("Ending by signal, signal = %d\n", WTERMSIG(status));
        }
    }
}

//ex3
void func(int signal_number){
    printf("Jump to function to call interrupt signal!\n");
    wait(NULL);
}

void usingSignal(__pid_t child_pid){
    int status;
    child_pid = fork();
    if(0 == child_pid){
        printf("Child process terminate\n");
        while(1);
    }
    else{
        signal(SIGCHLD, func);
        printf("Parent process!\n");
        while(1);
    }
}