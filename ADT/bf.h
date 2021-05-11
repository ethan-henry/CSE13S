#ifndef NIL
#define NIL (void *)0
#endif

#ifndef __BF_H__
#define __BF_H__

#include "bv.h"
#include <inttypes.h>
#include <stdbool.h>
#include "speck.h"

typedef struct BloomFilter {
  uint64_t primary[2];
  uint64_t secondary[2];
  uint64_t tertiary[2];
  BitVector *filter;
} BloomFilter;

BloomFilter *bf_create(uint32_t size);

void bf_delete(BloomFilter *bf);

void bf_insert(BloomFilter *bf, char *key);

bool bf_probe(BloomFilter *bf, char *key);

#endif
