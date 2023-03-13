#include "../project_server/util_functions.h"

int main() {
    char *num_str = "0_123456# 789a";

    if (valid_number_format(num_str, 15)) {
        return 1;
    }
    else {
        return 0;
    }
}
