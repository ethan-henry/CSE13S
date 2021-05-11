#include "parser.h"
#include <regex.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK 4096

static char *words[BLOCK] = {NULL};

char *next_word(FILE *infile, regex_t *word_regex) {
  static uint32_t index = 0;
  static uint32_t count = 0;
  if (!index) {
    clear_words();
    regmatch_t match;
    uint32_t matches = 0;
    char buffer[BLOCK] = {0};

    while (!matches) {
      if (!fgets(buffer, BLOCK, infile)) {
        return NULL;
      }
      char *cursor = buffer;
      for (uint16_t i = 0; i < BLOCK; i += 1) {
        if (regexec(word_regex, cursor, 1, &match, 0)) {
          break;
        }
        if (match.rm_so < 0) {
          break;
        }
        uint32_t start = (uint32_t)match.rm_so;
        uint32_t end = (uint32_t)match.rm_eo;
        uint32_t length = end - start;

        words[i] = (char *)calloc(length + 1, sizeof(char));
        if (!words[i]) {
          perror("calloc");
          exit(1);
        }
        memcpy(words[i], cursor + start, length);
        cursor += end;
        matches += 1;
      }
      count = matches;
    }
  }
  char *word = words[index];
  index = (index + 1) % count;
  return word;
}

void clear_words(void) {
  for (uint16_t i = 0; i < BLOCK; i += 1) {
    if (words[i]) {
      free(words[i]);
      words[i] = NULL;
    }
  }
  return;
}
