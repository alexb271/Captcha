#include "server.h"

int main() {
    CaptchaServer server = captcha_server_new("127.0.0.1", 9080);
    captcha_server_accept(&server);
    captcha_server_send_math_captcha(&server);

    return 0;
}
