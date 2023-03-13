#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// network includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// project includes
#include "client.h"
#include "../project_server/request_type.h"

CaptchaClient captcha_client_new(const char *address, int port) {
    CaptchaClient client;

    client.client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client.client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    client.server_address.sin_family = AF_INET;
    client.server_address.sin_port= htons(port);
    client.server_address.sin_addr.s_addr = inet_addr(address);
    memset(client.server_address.sin_zero, '\0', sizeof(client.server_address.sin_zero));

    client.size_of_server_address = sizeof(client.server_address);

    int result = connect(client.client_socket,
                        (struct sockaddr *)&client.server_address,
                        client.size_of_server_address);

    if (result != 0) {
        client.connected = false;
    }
    else {
        client.connected = true;
    }

    return client;
}

void captcha_client_send(const CaptchaClient *self, const char *message, size_t len) {
    send(self->client_socket, message, len, 0);
}

void captcha_client_receive(const CaptchaClient *self, char *buffer, size_t len) {
    recv(self->client_socket, buffer, len, 0);
}

void captcha_client_disconnect(CaptchaClient *self) {
    char message = DISCONNECT;
    send(self->client_socket, &message, 1, 0);
    shutdown(self->client_socket, 3);
}


#define BUFSIZE 1024

int not_main() {
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
    server_address.sin_port= htons(9080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server_address.sin_zero, '\0', sizeof(server_address.sin_zero));

    result = connect(client_socket_descriptor,
                     (struct sockaddr *)&server_address,
                     size_of_server_address);

    if (result != 0) {
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }

    char operation = getchar() - 48;
    getchar(); // discard trailing newline
    send(client_socket_descriptor, &operation, 1, 0);

    recv(client_socket_descriptor, buffer, BUFSIZE, 0);
    printf("%s\n", buffer);

    fgets(buffer, BUFSIZE, stdin);
    // remove trailing newline
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }
    send(client_socket_descriptor, buffer, BUFSIZE, 0);

    // clear the buffer
    for (int i = 0; i < BUFSIZE; i++) {
        buffer[i] = '\0';
    }
    recv(client_socket_descriptor, buffer, BUFSIZE, 0);
    printf("%s\n", buffer);

    return 0;
}
