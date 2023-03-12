#pragma once

#include <ctype.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void get_two_random_numbers(uint8_t *num1, uint8_t *num2);
bool valid_number_format(const char *str, size_t len);
void remove_trailing_newline(char *str, size_t len);
