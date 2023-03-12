#pragma once

#include <ctype.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// An even-odd challange is simply picking the odd numbers
// from 9 randomly generated numbers. In the mask 0 means even
// and 1 means odd on the corresponding index.
#define CHALLANGE_SIZE 9

typedef struct {
    uint8_t numbers[CHALLANGE_SIZE];
    char mask[CHALLANGE_SIZE];
} EvenOddChallange;

void get_two_random_numbers(uint8_t *num1, uint8_t *num2);
EvenOddChallange generate_even_odd_challange();
bool valid_number_format(const char *str, size_t len);
void remove_trailing_newline(char *str, size_t len);
