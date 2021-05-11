#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "psn:"

void sieve(BitVector *v);
bool is_palendrome(char *v);
char *get_base(int32_t num, char *output, uint32_t base);
char *reverse(char *output, uint32_t i, uint32_t j);

// Main Function
int main(int32_t argc, char **argv) {
  char output[10];
  uint32_t x;
  bool n = false, p = false, s = false;
  int32_t c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'n':
      n = true;
      x = atoi(optarg);
      break;
    case 'p':
      p = true;
      break;
    case 's':
      s = true;
      break;
    }
  }
      
      if (!n) {
        x = 1000;
      }

  BitVector *bit = bv_create(x);
  sieve(bit);

      if (s) {
        for (uint32_t i = 0; i < bv_get_len(bit) + 1; i += 1) {
        if (bv_get_bit(bit, i) == 1) {
          printf("%d: prime", i);
          if (merc(bit, i)) {
            printf(", mersenne");
          }
          if (lucas(bit, i) || (i == 2)) {
            printf(", lucas");
          }
          if (fiba(bit, i)) {
            printf(", fibonacci");
          }
          if (bv_get_bit(bit, i) == 1) {
            printf("\n");
          }
        }
      }
     }

  if (p) {
     printf("\nBase  2\n---- --\n");
      for (uint32_t i = 0; i < bv_get_len(bit) + 1; i += 1) {
        if ((bv_get_bit(bit, i) == 1) &&
            (is_palendrome(get_base(i, output, 2)))) {
          printf("%d = %s\n", i, get_base(i, output, 2));
        }
      }
      printf("\nBase 10\n---- --\n");
      for (uint32_t i = 0; i < bv_get_len(bit) + 1; i += 1) {
        if ((bv_get_bit(bit, i) == 1) &&
            (is_palendrome(get_base(i, output, 10)))) {
          printf("%d = %s\n", i, get_base(i, output, 10));
        }
      }
      printf("\nBase 14\n---- --\n");
      for (uint32_t i = 0; i < bv_get_len(bit) + 1; i += 1) {
        if ((bv_get_bit(bit, i) == 1) &&
            (is_palendrome(get_base(i, output, 14)))) {
          printf("%d = %s\n", i, get_base(i, output, 14));
        }
      }
      printf("\nBase 18\n---- --\n");
      for (uint32_t i = 0; i < bv_get_len(bit) + 1; i += 1) {
        if ((bv_get_bit(bit, i) == 1) &&
            (is_palendrome(get_base(i, output, 18)))) {
          printf("%d = %s\n", i, get_base(i, output, 18));
        }
      }
  }

  bv_delete(bit);
  return 0;
}

// Function to test if an input is a Palendrome
// Input:
// 	v: string to be tested
// Returns:
// 	boolean value: True if is a Palendrome; False otherwise
bool is_palendrome(char *v) {
  uint32_t left = 0;
  uint32_t right = strlen(v) - 1;
  while (left < right) {
    if (v[right] != v[left]) {
      return false;
    }
    left += 1;
    right -= 1;
  }
  return true;
}

// Function to convert a Base 10 number into any other Base
// Inputs:
// 	num: Decimal Number
//	output: String to be used
//	base: Desired base to convert to
//
// Returns:
//	String of numbers in the desired base
char *get_base(int32_t num, char *output, uint32_t base) {
  uint32_t i = 0;
  while (num != 0) {
    uint32_t r = num % base;
    if (r >= 10) {
      output[i++] = 97 + (r - 10);
    } else {
      output[i++] = 48 + r;
    }
    num = num / base;
  }
  if (i == 0) {
    output[i++] = '0';
  }
  output[i] = '\0';
  output = reverse(output, 0, i - 1);
  return output;
}

// Function to reverse input
// Inputs:
// 	output: string to be reversed
// 	i: first character of the string
// 	j: last character of the string
// Returns:
// 	A string that is reverse from the original input string
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
