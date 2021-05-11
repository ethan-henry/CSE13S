#include "sieve.h"
#include "bv.h"
#include <math.h>
#include <stdio.h>

static uint32_t fib1 = 0;
static uint32_t fib2 = 1;
static uint32_t luc1 = 2;
static uint32_t luc2 = 1;
static uint32_t temp1 = 0;

void sieve(BitVector *v) {
  bv_set_all_bits(v);
  bv_clr_bit(v, 0);
  bv_clr_bit(v, 1);
  bv_set_bit(v, 2);
  for (uint32_t i = 2; i <= sqrt(bv_get_len(v)); i += 1) {
    if (bv_get_bit(v, i) == 1) {
      for (uint32_t k = 0; (k + i) * i <= bv_get_len(v); k += 1) {
        bv_clr_bit(v, (k + i) * i);
      }
    }
  }
  return;
}

bool merc(BitVector *v, uint32_t i) {
  uint32_t t = log(i + 1) / log(2);
  if ((bv_get_bit(v, t) == 1) && (temp1 != t)) {
    temp1 = t;
    return true;
  }
  return false;
}

bool lucas(BitVector *v, uint32_t i) {
  bv_set_bit(v, 2);
  uint32_t temp = 0;
  if (i < luc2 + luc1) {
    return false;
  }
  if (i > luc1 + luc2) {
    temp = luc1;
    luc1 = luc2;
    luc2 = luc2 + temp;
  }
  if ((i == luc1 + luc2) && (bv_get_bit(v, i))) {
    return true;
  }
  return false;
}

bool fiba(BitVector *v, uint32_t i) {
  uint32_t temp = 0;
  if (i < fib1 + fib2) {
    return false;
  }
  if (i > fib1 + fib2) {
    temp = fib1;
    fib1 = fib2;
    fib2 = fib2 + temp;
  }
  if ((i == fib1 + fib2) && (bv_get_bit(v, i))) {
    return true;
  }
  return false;
}
