#include "bv.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

BitVector *bv_create(uint32_t bit_len) {
  BitVector *v = (BitVector *)malloc(sizeof(BitVector));
  if (!v) {
    printf("ERROR: MALLOC FAILED\n");
    return NULL;
  }
  v->length = bit_len;
  v->vector = (uint8_t *)calloc((bit_len / 8) + 1, sizeof(uint8_t));
  if (!v->vector) {
    printf("ERROR: CALLOC FAILED\n");
    return NULL;
  }
  return v;
}

void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
  v->vector = NULL;
  v = NULL;
  return;
}

uint32_t bv_get_len(BitVector *v) {
  uint32_t output = v->length;
  return output;
}

void bv_set_bit(BitVector *v, uint32_t i) {
  uint32_t pos = i % 8;
  uint32_t num = i / 8;
  uint32_t flag = 1;
  flag = flag << pos;
  v->vector[num] = v->vector[num] | flag;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
  uint32_t pos = 0;
  uint32_t num = 0;
  pos = i % 8;
  num = i / 8;
  uint8_t flag = 1;
  flag = flag << pos;
  flag = ~flag;
  v->vector[num] = v->vector[num] & flag;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  uint32_t pos = i % 8;
  uint32_t num = i / 8;
  uint32_t flag = 1;
  flag = flag << pos;
  uint8_t output = 0;
  uint32_t temp = v->vector[num] & flag;
  if (temp != 0) {
    output = 1;
  }
  return output;
}

void bv_set_all_bits(BitVector *v) {
  uint8_t flag = 0;
  flag = ~flag;
  for (uint32_t i = 0; i < (v->length / 8) + 1; i++) {
    v->vector[i] = v->vector[i] | flag;
  }
}
