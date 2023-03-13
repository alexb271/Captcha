#pragma once

// basic includes
#include <stdbool.h>

// network includes
#include <arpa/inet.h>

typedef struct {
    int client_socket;
    struct sockaddr_in server_address;
    socklen_t size_of_server_address;

    bool connected;
} CaptchaClient;

CaptchaClient captcha_client_new(const char *address, int port);
void captcha_client_send(const CaptchaClient *self, const char *message, size_t len);
void captcha_client_receive(const CaptchaClient *self, char *buffer, size_t len);
void captcha_client_disconnect(CaptchaClient *self);
