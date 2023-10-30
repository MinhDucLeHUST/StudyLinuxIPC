#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipefd[1]);  // Close the write end of the pipe

        // Read from the pipe
        ssize_t bytesRead = read(pipefd[0], buffer, BUFFER_SIZE);
        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Child process received: %s", buffer);

        close(pipefd[0]);  // Close the read end of the pipe
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipefd[0]);  // Close the read end of the pipe

        const char* message = "Hello from the parent process!";
        size_t messageLength = strlen(message);

        // Write to the pipe
        ssize_t bytesWritten = write(pipefd[1], message, messageLength);
        if (bytesWritten == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);  // Close the write end of the pipe
        // wait(NULL);  // Wait for the child process to finish
        exit(EXIT_SUCCESS);
    }

    return 0;
}
