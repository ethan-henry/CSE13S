#ifndef __SIEVE_H__
#define __SIEVE_H__

#include "bv.h"
#include <math.h>
#include <stdio.h>

// Function to test if a number is a prime
// Inputs:
// 	v: BitVector
// Returns:
// 	None; Sets bits in provided BitVector if is a prime
void sieve(BitVector *v);

// Function to test if a number is a Mercenne Prime
// Inputs:
// 	v: BitVector of Primes
// 	i: int input to be tested
// Returns:
// 	True if mercenne prime, false otherwise
bool merc(BitVector *v, uint32_t i);

// Function to test if a number is a Lucas Prime
// Inputs:
//      v: BitVector of Primes
//      i: int input to be tested
// Returns:
//      True if lucas prime, false otherwise
bool lucas(BitVector *v, uint32_t i);

// Function to test if a number is a Fibonacci Prime
// Inputs:
//      v: BitVector of Primes
//      i: int input to be tested
// Returns:
//      True if fibonacci prime, false otherwise
bool fiba(BitVector *v, uint32_t i);

#endif
