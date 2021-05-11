#ifndef __BASE_H__
#define __BASE_H__

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
// Input String, followed by base input and base output
char *get_base_char(char *input, uint32_t base_in, uint32_t base_out);

uint32_t get_base10_char(char *num, uint32_t base);

uint32_t val(char c);

char *reverse(char *output, uint32_t i, uint32_t j);

#endif
