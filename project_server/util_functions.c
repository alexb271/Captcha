// standard library
#include <stdio.h>
#include <stdlib.h>

// project
#include "util_functions.h"

void get_two_random_numbers(uint8_t *num1, uint8_t *num2) {
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

EvenOddChallange generate_even_odd_challange() {
    FILE *rng = fopen("/dev/urandom", "r");

    if (rng == NULL) {
        fprintf(stderr, "Error: unable to open /dev/urandom");
        fclose(rng);
        exit(EXIT_FAILURE);
    }

    EvenOddChallange challange;
    for (size_t i = 0; i < CHALLANGE_SIZE; i++) {
        challange.numbers[i] = fgetc(rng);
        if (challange.numbers[i] % 2 == 0) {
            challange.mask[i] = 0;
        }
        else {
            challange.mask[i] = 1;
        }
    }

    fclose(rng);
    return challange;
}

bool valid_number_format(const char *str, size_t len) {
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

void remove_trailing_newline(char *str, size_t len) {
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

