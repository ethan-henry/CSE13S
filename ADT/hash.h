#ifndef NIL
#define NIL (void *)0
#endif

#ifndef __HASH_H__
#define __HASH_H__

#include "gs.h"
#include "ll.h"
#include "speck.h"
#include <inttypes.h>

typedef struct HashTable {
  uint64_t salt[2];
  uint32_t length;
  ListNode **heads;
} HashTable;

// CREATES HASH TABLE
// INPUTS:
// 	length: Length of the HASH TABLE
// RETURNS:
// 	Pointer to the Hash Table
HashTable *ht_create(uint32_t length);

void ht_delete(HashTable *h);

// LOOKS UP A HASH TABLE NODE
// INPUTS:
// 	h: The Hash Table
// 	key: The oldspeak of the GS Object trying to be found
// RETURNS:
// 	Returns LL NODE of searched for Key, otherwise returns NULL
ListNode *ht_lookup(HashTable *h, char *key);

// INSERTS A GS OBJECT INTO THE HASH TABLE
// INPUTS:
// 	h: Hash Table
// 	gs: Good Speak Object
void ht_insert(HashTable *h, GoodSpeak *gs);

// HOW MANY NON-NULL INDICSE ARE THERE
// INPUTS:
// 	h: HASH TABLE
uint32_t ht_count(HashTable *h);

void ht_print(HashTable *h);

#endif
