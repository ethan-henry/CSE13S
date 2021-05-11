#include "include_h_file.h"
#include <stdlib.h>
#include <string.h>

Word *word_create(uint8_t *syms, uint64_t len) {
  Word *new = calloc(1, sizeof(Word));
  if (new) {
    new->syms = (uint8_t *)calloc(len, sizeof(uint8_t));
    new->len = len;
    if (syms) {
      if (new->syms) {
        for (uint32_t index = 0; index < len - 1; index++) {
          new->syms[index] = syms[index];
        }
        return new;
      }
    } else {
     return new;
    }
  }
  return NULL;
}

Word *word_append_sym(Word *w, uint8_t sym) { 
  if (w) {
    if (w->syms){
      Word *new = word_create(w->syms, w->len + 1);
      new->syms[w->len] = sym;
      return new;
    }
  }
  Word *new_empty = word_create(&sym, 1);
  return new_empty;
}

void word_delete(Word *w) {
  if (w) {
    if (w->syms) {
      free(w->syms);
      w->syms = NULL;
    }
    free(w);
    w = NULL;
  }
  return;
}

void wt_delete(WordTable *w) {
  for (uint32_t index = 0; index < MAX_CODE; index++) {
      word_delete(w[index]);
      w[index] = NULL;
  }
  free(w);
  w = NULL;
  return;
}

WordTable *wt_create(void) {
  WordTable *new = (WordTable *)calloc(MAX_CODE, sizeof(Word));
  if (new) {
    Word *empty = word_create(NULL, 0);
    new[EMPTY_CODE] = empty;
    return new;
  }
  return NULL;
}

void wt_reset(WordTable *wt) {
  for (uint32_t index = 2; index < MAX_CODE; index++) {
    if(wt[index]) {
      word_delete(wt[index]);
      wt[index] = NULL;
    }
  }
  return;
}
