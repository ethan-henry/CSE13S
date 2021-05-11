#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "Absqip:r:n:"

int32_t main(int32_t argc, char **argv) {
  bool a = false, b = false, s = false, q = false, i = false;
  bool r = false;
  int32_t c = 0;
  uint32_t size = 100, num = 100;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {		// Parses the Command Line Arguments
    switch (c) {
    case 'A':
      a = true;
      break;
    case 'b':
      b = true;
      break;
    case 's':
      s = true;
      break;
    case 'q':
      q = true;
      break;
    case 'i':
      i = true;
      break;
    case 'p':
      num = atoi(optarg);
      break;
    case 'r':
      r = true;
      srand(atoi(optarg));
      break;
    case 'n':
      size = atoi(optarg);
      break;
    }
  }
  if (!r) {
    srand(8222022);
  }
  if (num > size) {
    num = size;
  }

  uint32_t *temp = (uint32_t *)calloc(size, sizeof(uint32_t));		// Creates 2 Arrays, one for the numbers, and one with
  uint32_t *arr = (uint32_t *)calloc(size, sizeof(uint32_t));		// the original numebrs

  if ((!temp) || (!arr)) {
    free(arr);
    free(temp);
    printf("ERROR: FAILED TO ALLOC MEMORY\n");
    return 1;
  }
  for (uint32_t index = 0; index < size; index++) {
    arr[index] = rand() & 0x3FFFFFFF;
    temp[index] = arr[index];
  }
  if (a) {
    Bubble_Sort(arr, size);
    for (uint32_t index = 0; index < num; index++) {
      if (index % 7 == 0) {
        printf("\n");
      }
      printf("%13u", arr[index]);
    }
    for (uint32_t index1 = 0; index1 < size; index1++) {
      arr[index1] = temp[index1];
    }
    printf("\n");
    Shell_Sort(arr, size);
    for (uint32_t index = 0; index < num; index++) {
      if (index % 7 == 0) {
        printf("\n");
      }
      printf("%13u", arr[index]);
    }
    for (uint32_t index1 = 0; index1 < size; index1++) {
      arr[index1] = temp[index1];
    }
    printf("\n");
    printf("Quick Sort\n%u elements, %u moves, %u compares", size,
        Quick_Sort(arr, 0, size - 1), get_q_com());
    for (uint32_t index = 0; index < num; index++) {
      if (index % 7 == 0) {
        printf("\n");
      }
      printf("%13u", arr[index]);
    }
    for (uint32_t index1 = 0; index1 < size; index1++) {
      arr[index1] = temp[index1];
    }
    printf("\n");
    Binary_Insertion_Sort(arr, size);
    for (uint32_t index = 0; index < num; index++) {
      if (index % 7 == 0) {
        printf("\n");
      }
      printf("%13u", arr[index]);
    }
    printf("\n");
    a = false, b = false, s = false, q = false, i = false;
  }
  if (b) {
    Bubble_Sort(arr, size);
    for (uint32_t index = 0; index < num; index++) {
      if (index % 7 == 0) {
        printf("\n");
      }
      printf("%13u", arr[index]);
    }
    printf("\n");
    for (uint32_t index1 = 0; index1 < size; index1++) {
      arr[index1] = temp[index1];
    }
  }
  if (s) {
    Shell_Sort(arr, size);
    for (uint32_t index = 0; index < num; index++) {
      if (index % 7 == 0) {
        printf("\n");
      }
      printf("%13u", arr[index]);
    }
    printf("\n");
    for (uint32_t index1 = 0; index1 < size; index1++) {
      arr[index1] = temp[index1];
    }
  }
  if (q) {
    printf("Quick Sort\n%u elements, %u moves, %u compares", size,
        Quick_Sort(arr, 0, size - 1), get_q_com());

    for (uint32_t index = 0; index < num; index++) {
      if (index % 7 == 0) {
        printf("\n");
      }
      printf("%13u", arr[index]);
    }
    printf("\n");

    for (uint32_t index1 = 0; index1 < size; index1++) {
      arr[index1] = temp[index1];
    }
  }
  if (i) {
    Binary_Insertion_Sort(arr, size);
    for (uint32_t index = 0; index < num; index++) {
      if (index % 7 == 0) {
        printf("\n");
      }
      printf("%13u", arr[index]);
    }
    printf("\n");
    for (uint32_t index1 = 0; index1 < size; index1++) {
      arr[index1] = temp[index1];
    }
  }
  free(arr);
  free(temp);
  return 0;
}
