#ifndef __SHELL_H__
#define __SHELL_H__

#include <inttypes.h>
#include <stdio.h>

// Inputs:
// 	n: previous gap length
// Returns:
// 	next gap size
uint32_t gap(uint32_t n);

// Inputs:
// 	arr: Array to bd Sorted
// 	len: Length of Array
// Returns:
// 	None
void Shell_Sort(uint32_t arr[], uint32_t len);

#endif
