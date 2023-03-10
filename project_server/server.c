#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// network includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 1024

int main() {
    const char *hello = "Hello from server";
    const char *confirm = "Message received";
    char buffer[BUFSIZE] = {'\0'};
    int result;

    int server_socket_descriptor;
    struct sockaddr_in server_address;

    int incoming_socket_desriptor;
    struct sockaddr_storage incoming_address;
    socklen_t size_of_incoming_address = sizeof(incoming_address);

    server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_descriptor == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port= htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server_address.sin_zero, '\0', sizeof(server_address.sin_zero));

    result = bind(server_socket_descriptor,
                  (struct sockaddr *)&server_address,
                  sizeof(server_address));

    if (result != 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    result = listen(server_socket_descriptor, 5);

    if (result != 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    incoming_socket_desriptor = accept(server_socket_descriptor,
                                       (struct sockaddr *)&incoming_address,
                                       &size_of_incoming_address);

    send(incoming_socket_desriptor, hello, strlen(hello), 0);
    read(incoming_socket_desriptor, buffer, BUFSIZE);

    printf("%s\n", buffer);

    if (strlen(buffer) > 0) {
        send(incoming_socket_desriptor, confirm, strlen(confirm), 0);
    }

    return 0;
}
