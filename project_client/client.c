#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// network includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

int main() {
    int result;
    char buffer[BUFSIZE] = {0};
    int client_socket_descriptor;

    struct sockaddr_in server_address;
    socklen_t size_of_server_address = sizeof(server_address);

    client_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_descriptor == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port= htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server_address.sin_zero, '\0', sizeof(server_address.sin_zero));

    result = connect(client_socket_descriptor,
                     (struct sockaddr *)&server_address,
                     size_of_server_address);

    if (result != 0) {
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }

    recv(client_socket_descriptor, buffer, BUFSIZE, 0);
    printf("%s\n", buffer);

    fgets(buffer, BUFSIZE, stdin);
    send(client_socket_descriptor, buffer, BUFSIZE, 0);

    // clear the buffer
    for (int i = 0; i < BUFSIZE; i++) {
        buffer[i] = '\0';
    }
    recv(client_socket_descriptor, buffer, BUFSIZE, 0);
    printf("%s\n", buffer);

    return 0;
}
