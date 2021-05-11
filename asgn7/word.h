#ifndef __WORD_H__
#define __WORD_H__

#include <inttypes.h>

typedef struct Word {
  uint8_t *syms;
  uint32_t len;
} Word;

typedef Word * WordTable;

// Creates a Word
// INPUTS:
// 	syms: array of symbols
// 	len: length of the array
// RETURNS:
// 	New word object 
Word *word_create(uint8_t *syms, uint64_t len);

// Appends a symbol to the end of a word
// INPUTS:
// 	w: Word to be appended to
// 	sym: symbol to be appended
// RETURNS:
// 	appended word
Word *word_append_sym(Word *w, uint8_t sym);

// Deletes word
// INPUTS:
// 	w: word to delete
void word_delete(Word *w);

// Creates a Word Table
// RETURNS:
// 	new word table object with an empty word at empty code
WordTable *wt_create(void);

// Resets Word table by deleting all words except for the empty word
// INPUTS:
// 	wt: word table to reset
void wt_reset(WordTable *wt);

// Deletes a whole Wordtable, object and children
// INPUTS:
// 	wt: word table to delete
void wt_delete(WordTable *wt);

#endif
