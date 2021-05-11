#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include "trie.h"
#include "code.h"
TrieNode *trie_node_create(uint16_t code) {
  TrieNode *new = (TrieNode *)calloc(1, sizeof(TrieNode));
  if (new) {
//    printf("CODE INSERTED: %u\n", code);
    new->code = code;
    return new;
  }
  return NULL;
}

TrieNode *trie_create(void) {
  TrieNode *new = trie_node_create(EMPTY_CODE);
  if (new) {
    new->code = EMPTY_CODE;
    return new;
  }
  return NULL;
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  if (n && sym) {
    if (n->children[sym]) {
      return n->children[sym];
    } else {
      return NULL;
    }
  }
  return NULL;
}

void trie_reset(TrieNode *root) {
  if (root) {
    for (uint32_t index = 0; index < ALPHABET; index++) {
        trie_delete(root->children[index]);
        root->children[index] = NULL;
    }
    return;
  }
}

void trie_delete(TrieNode *n) {
  if (n == NULL) {
    return;
  } else {
    for (uint16_t index = 0; index < 256; index++) {
      if (n->children[index] != NULL) {
        trie_delete(n->children[index]);
        n->children[index] = NULL;
      }
    }
  }
  trie_node_delete(n);
  n = NULL;
  return;
}

void trie_node_delete(TrieNode *n) {
  if (n) {
    free(n);
  }
  return;
}
