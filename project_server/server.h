#pragma once

// basic includes
#include <stdbool.h>
#include <stdint.h>

// network includes
#include <arpa/inet.h>

// project includes
#include "request_type.h"

typedef struct {
    int server_socket;
    struct sockaddr_in server_address;

    int incoming_socket;
    struct sockaddr_storage incoming_address;
    socklen_t size_of_incoming_address;
    bool connection_is_active;

    const char *log_file_path;
    const char *stat_file_path;
    uint32_t success_count;
    const char *success_message;
    uint32_t fail_count;
    const char *fail_message;
} CaptchaServer;

CaptchaServer captcha_server_new(const char *address, int port);
void captcha_server_run(CaptchaServer *self);
bool captcha_server_accept(CaptchaServer *self);
void captcha_server_send_math_captcha(CaptchaServer *self);
void captcha_server_send_even_odd_captcha(CaptchaServer *self);
void captcha_server_send_stats(const CaptchaServer *self);
void captcha_server_write_stats_to_file(const CaptchaServer *self);
void captcha_server_load_stats_from_file(CaptchaServer *self);
void captcha_server_log_event(const CaptchaServer *self, const char *event);
