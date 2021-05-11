#include "include_h_file.h"
#define OPTIONS "vi:o:"

uint32_t bit_len(uint32_t num);

int32_t main(int32_t argc, char **argv) {
  bool v = false, i = false, o = false;
  int32_t opt = 0;
  char *input, *output;
  int32_t infile = STDIN_FILENO;
  int32_t outfile = STDOUT_FILENO;
  while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
    switch(opt) {
    case'v':
      v = true;
      break;
    case'i':
      i = true;
      input = optarg;
      break;
    case'o':
      output = optarg;
      o = true;
      break;
    }
  }

  if (i) {
    infile = open(input, O_RDONLY);
  }

  FileHeader *header = calloc(1, sizeof(FileHeader));
  read_header(infile, header);
  if (header->magic != MAGIC) {
    close(infile);
    free(header);
    printf("BAD MAGIC NUMBER\n");
    return 1;
  }

  if (o) {
    outfile = open(output, O_WRONLY | O_CREAT | O_TRUNC, header->protection);
  }
  WordTable *table = wt_create();
  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;
  while (read_pair(infile, &curr_code, &curr_sym, bit_len(next_code))) {
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    buffer_word(outfile, table[next_code]);
    next_code = next_code + 1;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);
  if (v) {
    printf("Compressed file size: %lu\n", num_decom + sizeof(FileHeader));
    printf("Uncompressed file size: %u\n", num_com + 1);
    printf("Compression ratio: %.2f%c\n", 100 * (1 - (((float) num_com + 1 )/ (float) (num_decom + sizeof(FileHeader)))), 37);
  }
  if (header) {
    free(header);
  }
  close(infile);
  close(outfile);
  wt_delete(table);
   return 0;
}

uint32_t bit_len(uint32_t num) {
  uint32_t output = 0;
  uint16_t flag = 1;
  for (uint32_t index = 0; index < 15; index++) {
    if (((flag << index) & num) != 0) {
      output = index;
    }
  }
  return output + 1;
}
