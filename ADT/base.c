#include <inttypes.h>
#include <stdio.h>
#include "base.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *get_base_char(char *input, uint32_t base_in, uint32_t base_out) {
  uint32_t num = get_base10_char(input, base_in);
  char *output = (char *)calloc(32, sizeof(char));
  uint32_t i = 0;
  if (num == -1) {
    free(output);
    return 0;
  }
  if (base_out <= 1) {
    free(output);
    return 0;
  };
  while (num != 0) {
    uint32_t r = num % base_out;
    if (r >= 10) {
      output[i++] = 65 + (r - 10);
    } else {
      output[i++] = 48 + r;
    }
    num = num / base_out;
  }
  if (i == 0) {
    output[i++] = '0';
  }
  output[i] = '\0';
  output = reverse(output, 0, i - 1);
  return output;
}

uint32_t get_base10_char(char * num, uint32_t base) {
  uint32_t pow = 1;
  uint32_t len = strlen(num);
  uint32_t output = 0;
  for (int32_t i = len - 1; i >= 0; i--) {
    if (val(num[i]) >= base) {
      return -1;
    }
    output += val(num[i]) * pow;
    pow = pow * base;
  }
  return output;
}

uint32_t val(char c) {
  uint32_t output = toupper(c);
  if (c >= 48 && c <= 57) {
    return output - 48;
  } else {
    return output - 55;
  }
}

char *reverse(char *output, uint32_t i, uint32_t j) {
  while (i < j) {
    char t = output[i];
    output[i] = output[j];
    output[j] = t;
    i += 1;
    j -= 1;
  }
  return output;
}
