#include "hash.h"
#include "gs.h"
#include "ll.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }
  return (HashTable *)NIL;
}

void ht_delete(HashTable *ht) {
  uint32_t index = 0;
  if (ht) {
    while (index < ht->length) {
      if (ht->heads[index] != NULL) {
        ll_delete(ht->heads[index]);
      }
      index += 1;
    }
    free(ht->heads);
    free(ht);
  }
  return;
}

void ht_insert(HashTable *ht, GoodSpeak *gs) {
  uint64_t index = hash(ht->salt, gs->oldspeak) % ht->length;
  ht->heads[index] = ll_insert(&ht->heads[index], gs);
  return;
}

uint32_t ht_count(HashTable *h) {
  uint32_t output = 0;
  uint32_t index = 0;
  while (index < h->length) {
    if (h->heads[index]) {
      output += 1;
    }
    index += 1;
  }
  return output;
}

ListNode *ht_lookup(HashTable *ht, char *key) {
  uint64_t index = hash(ht->salt, key) % ht->length;
  ListNode *output = ll_lookup(&ht->heads[index], key);
  return output;
}

void ht_print(HashTable *ht) {
  uint32_t index = 0;
  while (index < ht->length) {
    ll_print(ht->heads[index]);
    index += 1;
  }
  return;
}
