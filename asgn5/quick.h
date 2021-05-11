#ifndef __QUICK_H__
#define __QUICK_H__

#include <inttypes.h>
#include <stdio.h>

// Inputs:
// 	a: First number to be swapped
// 	b: second number to be swapped
// Returns:
// 	None
void swap(uint32_t *a, uint32_t *b);

// Inputs: 
// 	arr: Array
// 	left: index of left most number
// 	right: index of right most number
// Returns:
// 	index of Partition
uint32_t Partition(uint32_t arr[], int32_t left, int32_t right);

// Inputs: 
// 	arr: Array to Sort
// 	left: index of left most element
// 	right: index of right most element
// Returns:
// 	number of moves
uint32_t Quick_Sort(uint32_t arr[], int32_t left, int32_t right);

// Inputs:
// 	None
// Returns:
// 	number of Comparisons
uint32_t get_q_com(void);
#endif
