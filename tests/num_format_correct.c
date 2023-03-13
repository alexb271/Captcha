#include "../project_server/util_functions.h"

int main() {
    char *num_str = "0123456789";

    if (valid_number_format(num_str, 11)) {
        return 0;
    }
    else {
        return 1;
    }
}
