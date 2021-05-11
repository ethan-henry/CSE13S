#include "bf.h"
#include "bv.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>

static uint32_t size_bf = 0;

BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    size_bf = size;
    return bf;
  }
  return (BloomFilter *)NIL;
}

void bf_delete(BloomFilter *bf) {
  if (bf->filter) {
    bv_delete(bf->filter);
  }
  if (bf) {
    free(bf);
  }
  return;
}

void bf_insert(BloomFilter *bf, char *key) {
  bv_set_bit(bf->filter, hash(bf->primary, key) % size_bf);
  bv_set_bit(bf->filter, hash(bf->secondary, key) % size_bf);
  bv_set_bit(bf->filter, hash(bf->tertiary, key) % size_bf);
  return;
}

bool bf_probe(BloomFilter *bf, char *key) {
  bool output = false;
  uint8_t first = bv_get_bit(bf->filter, hash(bf->primary, key) % size_bf);
  uint8_t second = bv_get_bit(bf->filter, hash(bf->secondary, key) % size_bf);
  uint8_t third = bv_get_bit(bf->filter, hash(bf->tertiary, key) % size_bf);
  if ((first) && (second) && (third)) {
    output = true;
  }
  return output;
}

uint32_t bf_count(BloomFilter *b) {
  uint32_t output = 0;
  uint32_t index = 0;
  while (index < size_bf) {
    if (bv_get_bit(b->filter, index) == 1) {
      output += 1;
    }
    index += 1;
  }
  return output;
}
