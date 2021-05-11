#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 1
#include "io.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "endian.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "code.h"

uint8_t buffer[4096] = {0};
uint8_t pairs[4096] = {0};
uint32_t pairs_index = 0;
uint32_t read_index = 0;
uint8_t buffer_test[4096] = {0};
uint8_t words[4096] = {0};
uint32_t word_index = 0;
uint32_t place = 0;
uint32_t place_sym = 0;
uint32_t index_sym = 0;
uint32_t num_in = 0;
uint32_t num_out = 0;
uint32_t num_com = 0;
uint32_t num_decom = 0;

void write_header(int outfile, FileHeader *header) {
  struct stat finfo;
  fstat(outfile, &finfo);
  mode_t protect = finfo.st_mode;
  header->magic = MAGIC;
  header->protection = protect;
  if (is_big()) {
      header->protection = swap64(header->protection);
      header->magic = swap64(header->magic);
  } 
  write(outfile, header, sizeof(FileHeader));
  return;
}

void read_header(int infile, FileHeader *header) {
  read(infile, header, sizeof(FileHeader));
  if (is_big()) {
    header->protection = swap64(header->protection);
    header->magic = swap64(header->magic);
  } 
  return;
}

bool read_sym(int infile, uint8_t *syms) {
  if (index_sym == (place_sym - 1)) {
    index_sym = 0;
  }
  if (index_sym == 0) {
    place_sym = read(infile, buffer, 4096);
    num_out += place_sym;
  }
  if (place_sym == 0) {
    return false;
  }
  *syms = buffer[index_sym];
  index_sym++;
  return true;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
  uint32_t test = 0;
  if (is_big()) {
    code = swap16(code);
  }
  uint32_t power = 0;
  for (uint32_t index = 0; index < bitlen; index++) {
    uint32_t pos = index % bitlen;
    uint32_t flag = 1;
    flag = flag << pos;
    if ((pairs_index) / 8 == 4095) {
      flush_pairs(outfile);
      pairs_index = 0;
    }
    if ((code & flag) != 0) {
      pairs[pairs_index/8] |= 1 << (pairs_index % 8);
      test += pow(2, (pairs_index % 8));
    }
    power++;
    pairs_index++;
  }

  power = 0;
  uint32_t test_2 = 0;
  for (uint32_t index = 0; index < 8; index++) {
    uint32_t pos = index % 8;
    uint32_t flag = 1;
    flag = flag << pos;
    if ((pairs_index / 8) == 4095) {
      flush_pairs(outfile);
      pairs_index = 0;
    }
    if ((sym & flag) != 0) {
      pairs[pairs_index/8] |= 1 << (pairs_index % 8);
      test_2 += pow(2, (pairs_index % 8));
    }
  power++;
  pairs_index++;
  } 
}

void flush_pairs(int outfile) {
  num_in += (pairs_index / 8) + 1;
  write(outfile, pairs, (pairs_index / 8) + 1);
  for (uint32_t index_reset = 0; index_reset <= pairs_index; index_reset++) {
    pairs[index_reset] = 0;
  }
  pairs_index = 0;
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {
  uint16_t test_1 = 0;
  if (read_index == 0) {
    place = read(infile, buffer_test, 4096);
    num_decom += place;
  }
   
  uint32_t power = 0;
  for (uint32_t index = 0; index < bitlen; index++) {
    uint32_t flag = 1;
    flag = flag << (read_index % 8);
    if ((read_index / 8) == 4095) {
      place = read(infile, buffer_test, 4096);
      num_decom += place;
      read_index = 0;
    }
    if ((buffer_test[read_index/8] & flag) != 0) {
      test_1 += pow(2, power);
    }
    power++;
    read_index++;
  }

  if (is_big()) {
    *code = swap16(*code);
  }

  if (test_1 == STOP_CODE) {
    return false;
  }

  power = 0;
  uint8_t test_3 = 0;
  for (uint32_t index = 0; index < 8; index++) {
    uint32_t flag = 1;
    uint32_t pos = read_index % 8;
    flag = flag << pos;
    if ((read_index / 8) == 4095) {
      place = read(infile, buffer_test, 4096);
      num_decom += place;
      read_index = 0;
    }
    if ((buffer_test[read_index/8] & flag) != 0) {
      test_3 += pow(2, power);
    }
    power++;
    read_index++;
  }
    *sym = test_3;
    *code = test_1;
    return true;
}

void buffer_word(int outfile, Word *w) {
  for (uint32_t index_word = 0; index_word < w->len; index_word++) {
    if (word_index == 4095) {
      flush_words(outfile);
      word_index = 0;
    }
    words[word_index] = w->syms[index_word];
    word_index++;
  }
  return;
}

void flush_words(int outfile) {
  num_com += word_index;
  write(outfile, words, word_index);
  word_index = 0;
  return;
}

