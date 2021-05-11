#include "include_h_file.h"
#define OPTIONS "vi:o:"

uint32_t bit_len(uint32_t num);

int32_t main(int32_t argc, char **argv) {
  uint32_t *test = (uint32_t *)malloc(sizeof(uint32_t));
  printf("%d\n", *test);
  bool v = false, i = false, o = false;
  int32_t opt = 0;
  int32_t infile = STDIN_FILENO;
  int32_t outfile = STDOUT_FILENO; 
  char *input, *output;
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
      o = true;
      output = optarg;
      break;
    }
  }

  if (i) {
    infile = open(input, O_RDONLY);
  }

  if (o) {
    outfile = open(output, O_WRONLY | O_CREAT | O_TRUNC);
  }
  FileHeader *header = calloc(1, sizeof(FileHeader));
  write_header(outfile, header);
  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;
  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;
  while (read_sym(infile, &curr_sym)) {
    TrieNode *next_node = trie_step(curr_node, curr_sym);
    if (next_node) {
      prev_node = curr_node;
      curr_node = next_node;
    } else {
      buffer_pair(outfile, curr_node->code, curr_sym, bit_len(next_code));
      TrieNode *temp = trie_node_create(next_code);
      curr_node->children[curr_sym] = temp;
      for (uint32_t index = 0; index < ALPHABET; index++) {
        curr_node->children[curr_sym]->children[index] = NULL;
      }
      curr_node = root;
      next_code = next_code + 1;
    }
    if (next_code == MAX_CODE) {
      trie_reset(root);
      for (uint32_t index = 0; index < ALPHABET; index++) {
        root->children[index] = NULL;
      }
      curr_node = root;
      next_code = START_CODE;
    }
    prev_sym = curr_sym;
  }
  if (curr_node != root) {
    buffer_pair(outfile, prev_node->code, prev_sym, bit_len(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }
  buffer_pair(outfile, STOP_CODE, 0, bit_len(next_code));
  flush_pairs(outfile);
  if (v) {
    printf("Compressed file size: %lu\n", num_in + sizeof(FileHeader));
    printf("Uncompressed file size: %u\n", num_out);
    printf("Compression ratio: %.2f%c\n", 100 * (1 - ((float) (num_in + sizeof(FileHeader)) / ((float) num_out))), 37);
  }
  free(header);
  trie_delete(root);
  close(infile);
  close(outfile);
  return 0;
}

uint32_t bit_len(uint32_t num) {
  uint32_t output = 0;
  uint16_t flag = 1;
  for (uint32_t index = 0; index < 16; index++) {
    if (((flag << index) & num) != 0) {
      output = index;
    }
  }
  return output + 1;
}
