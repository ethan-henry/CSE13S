#include <inttypes.h>
#include <stdio.h>

uint32_t i_oper = 0;
uint32_t i_com = 0;

// Sorts using a Binary Search and Insertion Sort Method
void Binary_Insertion_Sort(uint32_t arr[], uint32_t len) {
  for (uint32_t i = 0; i < len; i++) {
    uint32_t value = arr[i];
    uint32_t left = 0;
    uint32_t right = i;
    while (left < right) {
      uint32_t mid = left + ((right - left) / 2);
      i_com += 1;
      if (value >= arr[mid]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    for (uint32_t j = i; j > left; j -= 1) {
      uint32_t temp = arr[j - 1];
      arr[j - 1] = arr[j];
      arr[j] = temp;
      i_oper += 3;
    }
  }
  printf("Binary Insertion Sort\n%u elements, %u moves, %u compares", len,
      i_oper, i_com);
}
