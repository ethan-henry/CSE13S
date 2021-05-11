#include "bubble.h"
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

uint32_t b_oper = 0;
uint32_t b_com = 0;

// Sorts using Bubble Sort
void Bubble_Sort(uint32_t arr[], uint32_t len) {
  for (uint32_t i = 0; i < len - 1; i += 1) {
    uint32_t j = len - 1;
    bool done = true;
    while (j > i) {
      b_com += 1;
      if (arr[j] < arr[j - 1]) {
        uint32_t temp = 0;
        temp = arr[j];
        arr[j] = arr[j - 1];
        arr[j - 1] = temp;
        b_oper += 3;
        done = false;
      }
      j -= 1;
    }
    if (done) {
      printf("Bubble Sort\n%u elements, %u moves, %u compares", len, b_oper,
          b_com);
      return;
    }
  }
  printf("Bubble Sort\n%u elements, %u moves, %u compares", len, b_oper, b_com);
  return;
}
