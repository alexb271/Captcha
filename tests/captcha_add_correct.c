#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../project_client/client.h"
#include "../project_server/request_type.h"

int main() {
    CaptchaClient client = captcha_client_new("127.0.0.1", 9080);

    char message = CAPTCHA_MATH;
    captcha_client_send(&client, &message, 1);

    char response_buffer[10] = { '\0' };
    captcha_client_receive(&client, response_buffer, 10);

    char num1[4] = { '\0' };
    size_t num1_idx = 0;
    char num2[4] = { '\0' };
    size_t num2_idx = 0;
    size_t buf_idx = 0;

    while (response_buffer[buf_idx] != ' ') {
        if (response_buffer[buf_idx] == '\0') { break; }

        num1[num1_idx] = response_buffer[buf_idx];
        num1_idx += 1;
        buf_idx += 1;
    }

    buf_idx += 3;

    while (response_buffer[buf_idx] != ' ') {
        if (response_buffer[buf_idx] == '\0') { break; }

        num2[num2_idx] = response_buffer[buf_idx];
        num2_idx += 1;
        buf_idx += 1;
    }

    char answer[10] = { '\0' };
    sprintf(answer, "%d", atoi(num1) + atoi(num2));
    captcha_client_send(&client, answer, 10);

    for (size_t i = 0; i < 10; i++) { response_buffer[i] = '\0'; }
    captcha_client_receive(&client, response_buffer, 10);
    printf("%s\n", response_buffer);

    captcha_client_disconnect(&client);

    return strcmp(response_buffer, "Success");
}
