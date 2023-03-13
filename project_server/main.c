#include "server.h"

int main() {
    CaptchaServer server = captcha_server_new("127.0.0.1", 9080, "server_stats.txt", "server_logs.txt");
    captcha_server_run(&server);

    return 0;
}
