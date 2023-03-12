#include "server.h"

int main() {
    CaptchaServer server = captcha_server_new("127.0.0.1", 9080);
    captcha_server_run(&server);

    return 0;
}
