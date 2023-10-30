#include "arpa/inet.h"
#include "errno.h"
#include "netinet/in.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/socket.h"
#include "unistd.h"

#define LISTEN_BACKLOG 50
#define BUFF_SIZE 256
#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

int main(int argc, char *const argv[]) {
    int port_number, len, otp;
    struct sockaddr_in server_add, client_add;
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_add.sin_family = AF_INET;  // sin = socket inet
    server_add.sin_port = port_number;
    server_add.sin_addr.s_addr = INADDR_ANY;

    // bind()
    if (bind(server_fd, (struct sockaddr *)&server_add, sizeof(server_add)) == -1)
        handle_error("bind()");
    // listen()
    if (listen(server_fd, LISTEN_BACKLOG) == -1)
        handle_error("listen()");

    len = sizeof(client_add);
    while (1) {
        printf("Server is listening at port: %d\n", port_number);
        int new_socket_fd = accept(server_fd, (struct sockaddr *)&client_add, (socklen_t *)&len);
        if (new_socket_fd == -1)
            handle_error("accept()");
        system("clear");
        char temp[BUFF_SIZE];
        inet_ntop(server_add.sin_family, (struct sockaddr *)&client_add, temp, sizeof(temp));
        printf("Server: got connection, port number: %d \n", client_add.sin_port);
    }
    close(server_fd);
    return 0;
}
