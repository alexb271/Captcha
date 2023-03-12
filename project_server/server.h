#pragma once

// basic includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// network includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
    int server_socket;
    struct sockaddr_in server_address;

    int incoming_socket;
    struct sockaddr_storage incoming_address;
    socklen_t size_of_incoming_address;
    bool connection_is_active;

    int success_count;
    const char *success_message;
    int fail_count;
    const char *fail_message;
} CaptchaServer;

CaptchaServer captcha_server_new(const char *address, int port);

bool captcha_server_accept(CaptchaServer *server);

void captcha_server_send_math_captcha(CaptchaServer *server);
