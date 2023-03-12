// basic includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// network includes
#include <sys/socket.h>
#include <netinet/in.h>

// project includes
#include "server.h"
#include "util_functions.h"

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

    server.stat_file_path = "server_stats.txt";
    server.success_message = "Success";
    server.fail_message = "Failed";
    captcha_server_load_stats_from_file(&server);

    printf("Success: %d\nFailed: %d\n", server.success_count, server.fail_count);

    return server;
}

bool captcha_server_accept(CaptchaServer *self) {
    self->incoming_socket = accept(self->server_socket,
                                     (struct sockaddr *)&self->incoming_address,
                                     &self->size_of_incoming_address);

    if (self->incoming_socket == -1) {
        self->connection_is_active = false;
        return false;
    }

    self->connection_is_active = true;
    return true;
}

void captcha_server_send_math_captcha(CaptchaServer *self) {
    if (!self->connection_is_active) {
        fprintf(stderr, "Error: Trying to send captcha while no connection is active");
        exit(EXIT_FAILURE);
    }

    uint8_t num1, num2;
    get_two_random_numbers(&num1, &num2);
    int math_captcha_result = num1 + num2;

    size_t message_buffer_size = 10;
    char message_buffer[message_buffer_size];
    sprintf(message_buffer, "%d + %d", num1, num2);
    send(self->incoming_socket, message_buffer, strlen(message_buffer), 0);

    recv(self->incoming_socket, message_buffer, message_buffer_size, 0);

    if (valid_number_format(message_buffer, message_buffer_size) &&
        atoi(message_buffer) == math_captcha_result)
    {
        self->success_count += 1;
        captcha_server_write_stats_to_file(self);
        send(self->incoming_socket, self->success_message, strlen(self->success_message), 0);
    }
    else {
        self->fail_count += 1;
        captcha_server_write_stats_to_file(self);
        send(self->incoming_socket, self->fail_message, strlen(self->fail_message), 0);
    }
}

void captcha_server_write_stats_to_file(const CaptchaServer *self) {
    FILE *stat_file = fopen(self->stat_file_path, "w");
    if (stat_file == NULL) {
        fprintf(stderr, "Error: Unable to write to stat file: %s\n", self->stat_file_path);
        fclose(stat_file);
        return;
    }

    fprintf(stat_file, "%d\n%d", self->success_count, self->fail_count);
    fclose(stat_file);
}

void captcha_server_load_stats_from_file(CaptchaServer *self) {
    FILE *stat_file = fopen(self->stat_file_path, "r");
    if (stat_file == NULL) {
        self->success_count = 0;
        self->fail_count = 0;
    }
    else {
        // 4-bit int value is a maximum of 10 decimal digits
        char buffer[11];
        size_t len;

        fgets(buffer, 11, stat_file);
        len = strlen(buffer);
        remove_trailing_newline(buffer, len);
        if (valid_number_format(buffer, strlen(buffer))) {
            self->success_count = atoi(buffer);
        }
        else {
            fprintf(stderr, "Error: Corrupted stat file: %s\n", self->stat_file_path);
            exit(EXIT_FAILURE);
        }

        fgets(buffer, 11, stat_file);
        len = strlen(buffer);
        remove_trailing_newline(buffer, len);
        if (valid_number_format(buffer, len)) {
            self->fail_count = atoi(buffer);
        }
        else {
            fprintf(stderr, "Error: Corrupted stat file: %s\n", self->stat_file_path);
            exit(EXIT_FAILURE);
        }
    }
}
