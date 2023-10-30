#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "string.h"

// Declare functions
void callSignalToWriteData();
void signalHandler(int count);
void workingWithPipe();

#define MSG_SIZE 100

char* msg1 = "Hello world 1\n";
char* msg2 = "Hello world 2\n";
char* msg3 = "Hello world 3\n";
char* msg4 = "Msg was wrote from function!";

char pipeBuffer[MSG_SIZE];
int fds[2];

int main(int argc, char const* argv[]) {
    int numberRead = 0;
    pid_t child_pid;
    if (pipe(fds) < 0) {
        printf("Pipe is not found!\n");
        exit(1);
    }

    child_pid = fork();

    if (child_pid == 0) {
        printf("This is child process!\n");  // dong vai tro` la reader
        // 1 process chi dong 1 vai tro, vi` the close write
        if (close(fds[1]) == -1)
            printf("Close write function was error!\n");

        while ((1)) {
            numberRead = read(fds[0], pipeBuffer, MSG_SIZE);
            if (numberRead == -1) {
                printf("Can't read data in Pipe!\n");
                exit(EXIT_FAILURE);
            } else if (numberRead == 0) {
                printf("End end-of-pipe!\n");
            } else {
                printf("Message: %s", pipeBuffer);
            }
        }
    } else {
        printf("This is parent process!\n");
        if (close(fds[0]) == -1)
            printf("Close read function was error!\n");
        write(fds[1], msg1, MSG_SIZE);
        write(fds[1], msg2, MSG_SIZE);
        write(fds[1], msg3, MSG_SIZE);
    }

    // callSignalToWriteData();

    return 0;
}

// Example 1: write data vào pipe, sau 2s đọc từng data trong pipe thông qua lệnh read
void workingWithPipe() {
    if (pipe(fds) < 0) {
        printf("Pipe is not found!\n");
        exit(1);
    }

    write(fds[1], msg1, MSG_SIZE);
    write(fds[1], msg2, MSG_SIZE);
    write(fds[1], msg3, MSG_SIZE);

    printf("Waiting 2 seconds!\n");
    sleep(2);

    for (int i = 0; i < 3; i++) {
        read(fds[0], pipeBuffer, MSG_SIZE);
        printf("msg[%d]: %s\n", i + 1, pipeBuffer);
    }
}

// Example 2: khi hàm đọc của pipe được gọi, nó sẽ đợi đến khi nào pipe có data đc write vào, sử dụng signal handle để minh họa cho vấn đề này
void signalHandler(int count) {
    printf("Call to signal handle function!\n");
    write(fds[1], msg4, MSG_SIZE);
}

void callSignalToWriteData() {
    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        fprintf(stderr, "Can not handle signal\n");
        exit(EXIT_FAILURE);
    }

    if (pipe(fds) < 0) {
        printf("Pipe is not found!\n");
        exit(1);
    }

    printf("Waiting 2 seconds!\n");
    sleep(2);
    // read pipe
    printf("Trying to read data in pipe!\n");
    read(fds[0], pipeBuffer, MSG_SIZE);
    printf("msg: %s\n", pipeBuffer);
}