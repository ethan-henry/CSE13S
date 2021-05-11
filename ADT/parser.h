#ifndef __PARSER_H__
#define __PARSER_H__

#include <regex.h>
#include <stdio.h>

char *next_word(FILE *infile, regex_t *word_regex);

void clear_words(void);

#endif
