#ifndef __IO_H__
#define __IO_H__

#include "word.h"
#include <inttypes.h>
#include <stdbool.h>

#define MAGIC 0x8badbeef

extern uint32_t num_out;
extern uint32_t num_in;
extern uint32_t num_com;
extern uint32_t num_decom;


typedef struct Fileheader {
uint32_t magic;
uint16_t protection;
} FileHeader;
// Reads the header of a file
// INPUTS:
// 	infile: file descriptor of file to read header from
// 	header: header object that will store the magic number and protection bits
void read_header(int infile, FileHeader *header);

// Writes the header to a file
// INPUTS:
// 	outfile: file descriptor of file to write header to
// 	header: header object that is written out
void write_header(int outfile, FileHeader *header);

// Reads a file one symbol at a time
// INPUTS:
// 	infile: file descriptor of file to read from
// 	sym: sym object to store the symbol across function calls
// RETURNS:
// 	false if there are no more symbols to read, true otherwise
bool read_sym(int infile, uint8_t *sym);

// Inserts pairs of codes and symbols into a buffer
// INPUTS:
// 	outfile: file descriptor of file to write the code to if the buffer is filled
// 	code: code to insert
// 	sym: symbol to insert
// 	bitlen: minimum number of bits needed to represent the code
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen);

// Writes out pairs to the file
// INPUTS:
// 	outfile: file descriptor of file to write pairs to
void flush_pairs(int outfile);

// Reads a file one pair at a time
// INPUTS:
// 	infile: file descriptor of file to read from
// 	code: pointer to store code
// 	sym: pointer to store symbol
// 	bitlen: minimum number of bits needed to represent the code
// RETURNS:
// 	false if there are no more pairs to read, true otherwise
bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen);

// Inserts words into a buffer
// INPUTS:
//	outfile: file descriptor of file to write to if buffer is filled
//	w: word to insert
void buffer_word(int outfile, Word *w);

// Writes words out to a file
// INPUTS:
// 	outfile: file descriptor of file to write words to
void flush_words(int outfile);

#endif
