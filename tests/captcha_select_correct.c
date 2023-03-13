#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../project_client/client.h"
#include "../project_server/request_type.h"

int main() {
    CaptchaClient client = captcha_client_new("127.0.0.1", 9080);

    char message = CAPTCHA_EVEN_ODD;
    captcha_client_send(&client, &message, 1);

    char response_buffer[37] = { '\0' };
    captcha_client_receive(&client, response_buffer, 37);

    char answer[10] = { '\0' };
    size_t ans_idx = 0;
    size_t resp_idx = 0;

    char buf[4] = { '\0' };
    size_t buf_idx = 0;
    while (response_buffer[resp_idx] != '\0') {
        if (response_buffer[resp_idx] != ',') {
            buf[buf_idx] = response_buffer[resp_idx];
            buf_idx += 1;
        }
        else {
            int num = atoi(buf);
            if (num % 2 == 0) { answer[ans_idx] = '0'; }
            else { answer[ans_idx] = '1'; }
            ans_idx += 1;

            buf_idx = 0;
            for (size_t i = 0; i < 4; i++) { buf[i] = '\0'; }
        }
        resp_idx += 1;
    }

    captcha_client_send(&client, answer, 9);

    for (size_t i = 0; i < 30; i++) { response_buffer[i] = '\0'; }
    captcha_client_receive(&client, response_buffer, 30);

    captcha_client_disconnect(&client);
    return strcmp(response_buffer, "Success");
}
