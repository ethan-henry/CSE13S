#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

uint32_t s_oper = 0;
uint32_t s_com = 0;

// Calculates the Gap
uint32_t gap(uint32_t n) {
  if (n <= 2) {
    return 1;
  } else {
    return (5 * n) / 11;
  }
}

// Uses Shell Sort Method
void Shell_Sort(uint32_t arr[], uint32_t len) {
  static uint32_t test = 0;
  for (uint32_t step = gap(len); test != 1; step = gap(step)) {
    test = step;
    for (uint32_t i = step; i < len; i += 1) {
      for (uint32_t j = i; j >= step; j -= step) {
        s_com += 1;
        if (arr[j] < arr[j - step]) {
          uint32_t temp = arr[j];
          arr[j] = arr[j - step];
          arr[j - step] = temp;
          s_oper += 3;
        }
      }
    }
  }
  printf("Shell Sort\n%u elements, %u moves, %u compares", len, s_oper, s_com);
  return;
}
