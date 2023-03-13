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
