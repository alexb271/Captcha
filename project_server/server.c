// standard library
#include <ctype.h>

// project
#include "server.h"

CaptchaServer captcha_server_new(const char *address, int port) {
    CaptchaServer server;

    server.server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server.server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.server_address.sin_family = AF_INET;
    server.server_address.sin_addr.s_addr = inet_addr(address);
    server.server_address.sin_port = htons(port);
    memset(server.server_address.sin_zero, '\0', sizeof(server.server_address.sin_zero));

    int result;
    result = bind(server.server_socket,
                  (struct sockaddr *)&server.server_address,
                  sizeof(server.server_address));

    if (result != 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    result = listen(server.server_socket, 3);

    if (result != 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    server.size_of_incoming_address = sizeof(server.incoming_address);
    server.connection_is_active = false;
    server.success_count = 0;
    server.success_message = "Success";
    server.fail_count = 0;
    server.fail_message = "Failed";

    return server;
}

bool captcha_server_accept(CaptchaServer *server) {
    server->incoming_socket = accept(server->server_socket,
                                     (struct sockaddr *)&server->incoming_address,
                                     &server->size_of_incoming_address);

    if (server->incoming_socket == -1) {
        server->connection_is_active = false;
        return false;
    }

    server->connection_is_active = true;
    return true;
}

static void get_two_random_numbers(uint8_t *num1, uint8_t *num2) {
    FILE *rng = fopen("/dev/urandom", "r");

    if (rng == NULL) {
        fprintf(stderr, "Error: unable to open /dev/urandom");
        fclose(rng);
        exit(EXIT_FAILURE);
    }

    *num1 = fgetc(rng);
    *num2 = fgetc(rng);
    fclose(rng);
}

static bool valid_number_format(const char *str, size_t len) {
    bool valid_format = true;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '\0') {
            break;
        }
        if (!isdigit(str[i])) {
            valid_format = false;
            break;
        }
    }

    return valid_format;
}

void captcha_server_send_math_captcha(CaptchaServer *server) {
    if (!server->connection_is_active) {
        fprintf(stderr, "Error: Trying to send captcha while no connection is active");
        exit(EXIT_FAILURE);
    }

    uint8_t num1, num2;
    get_two_random_numbers(&num1, &num2);
    int math_captcha_result = num1 + num2;

    size_t message_buffer_size = 10;
    char message_buffer[message_buffer_size];
    sprintf(message_buffer, "%d + %d", num1, num2);
    send(server->incoming_socket, message_buffer, strlen(message_buffer), 0);

    recv(server->incoming_socket, message_buffer, message_buffer_size, 0);

    if (valid_number_format(message_buffer, message_buffer_size) &&
        atoi(message_buffer) == math_captcha_result)
    {
        server->success_count += 1;
        send(server->incoming_socket, server->success_message, strlen(server->success_message), 0);
    }
    else {
        server->fail_count += 1;
        send(server->incoming_socket, server->fail_message, strlen(server->fail_message), 0);
    }
}


