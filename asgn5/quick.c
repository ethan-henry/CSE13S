#include "quick.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

uint32_t q_oper = 0;
uint32_t q_com = 0;

// Swaps numbers
void swap(uint32_t *a, uint32_t *b) {
  q_oper += 3;
  uint32_t t = *a;
  *a = *b;
  *b = t;
}

//Calculates the partition
uint32_t Partition(uint32_t arr[], int32_t left, int32_t right) {
  uint32_t pivot = arr[right];
  int32_t i = (left - 1);
  for (int32_t j = left; j <= right - 1; j += 1) {
    q_com += 1;
    if (arr[j] < pivot) {
      i += 1;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[right]);
  return (i + 1);
}

// Recursive Function
uint32_t Quick_Sort(uint32_t arr[], int32_t left, int32_t right) {
  if (left < right) {
    uint32_t index = Partition(arr, left, right);
    Quick_Sort(arr, left, index - 1);
    Quick_Sort(arr, index + 1, right);
  }
  return q_oper;
}

uint32_t get_q_com(void) {
  return q_com;
}
