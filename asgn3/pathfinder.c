#include "stack.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define OPTIONS "udmi:"
#define ROWS 26
#define COLS 26

bool is_safe(int res[ROWS][COLS], int row, int curr_node);
bool get_matrix_u(
    Stack *item, int res[ROWS][COLS], int curr_node, bool test[ROWS]);
void print_matrix(int32_t res[][COLS]);

uint32_t num = 0, shortest = 0, min = 26;

// Main Function
int32_t main(int32_t argc, char **argv) {
  int32_t c = 0;
  FILE *fp = stdin;
  char *str;
  bool test[ROWS] = { false };
  unsigned char a = 0, b = 0;
  int32_t check = argc - 1;
  bool u = false, d = false, i = false;
  int32_t iarg = 0;
  Stack *item = stack_create();
  int32_t res[ROWS][COLS] = { { 0 } };
  while (check != 0) {					// Checks which arguments are input
    if (strcmp(argv[check], "-d") == 0) {
      d = true;
    }
    if (strcmp(argv[check], "-u") == 0) {
      u = true;
    }
    if (strcmp(argv[check], "-i") == 0) {
      i = true;
      iarg = check;
    }
    check -= 1;
  }
  if (u && d) {						// If both U and D are requested, prints
    printf("ERROR\n");					// ERROR
  }

  if (!i) {						// If no -i is entered, defaults to stdin
    if(!(u && d)) {
    while (fscanf(fp, "%c%c\n", &a, &b) != EOF) {
        if(a == b) {
          fscanf(fp, "%c%c\n", &a, &b);
        }
        res[toupper(a) - 65][toupper(b) - 65] = 1;
        if ((!d && !u) || (!d && u)) {
          res[toupper(b) - 65][toupper(a) - 65] = 1;
        }
      }
    fclose(fp);
    get_matrix_u(item, res, 0, test);
    printf("Number of paths found: %d\n", num);
    if(num > 0) {
      printf("Length of shortest path found: %d\n", min);
    } else {
      printf("No paths found!\n");
    }
  }
}
  if (i) {						// If -i is provided, sets the file to open
    str = argv[iarg + 1];				// as the provided file
  }


  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'i':
      str = optarg;
      if (!u && !d) {
        fp = fopen(optarg, "r");			// Makes the matrix as an undirected graph
        while (fscanf(fp, "%c%c\n", &a, &b) != EOF) {	// This is the default
            if (a == b) {
              fscanf(fp, "%c%c\n", &a, &b);
              continue;
            }
            res[toupper(a) - 65][toupper(b) - 65] = 1;
            res[toupper(b) - 65][toupper(a) - 65] = 1;
        }
        fclose(fp);
        get_matrix_u(item, res, 0, test);
        printf("Number of paths found: %d\n", num);
        if(num > 0) {
          printf("Length of shortest path found: %d\n", min);
        } else {
          printf("No paths found!\n");
        }
      }
      break;
    case 'm':
      if (!(u && d)) {
        print_matrix(res);
      }
      break;
    case 'u':						// Makes the matrix as an undirected graph
      if ((i) && (!(u && d))) {
      fp = fopen(str, "r");
      while (fscanf(fp, "%c%c\n", &a, &b) != EOF) {
        if (a == b) {
          fscanf(fp, "%c%c\n", &a, &b);
        }
        if ((isalpha(a) == 0) || (isalpha(b) == 0)) {
          printf("ERROR\n");
          break;
        }
          res[toupper(a) - 65][toupper(b) - 65] = 1;
          res[toupper(b) - 65][toupper(a) - 65] = 1;
      }
      fclose(fp);
      get_matrix_u(item, res, 0, test);
      printf("Number of paths found: %d\n", num);
      if(num > 0) {
        printf("Length of shortest path found: %d\n", min);
      } else {
        printf("No paths found!\n");
      }
      }
      break;

    case 'd':					// Makes the matrix as a directed graph
      if ((i) && (!(u && d))) {
      fp = fopen(str, "r");
      while (fscanf(fp, "%c%c\n", &a, &b) != EOF) {
        if (a == b) {
          fscanf(fp, "%c%c\n", &a, &b);
        }
        if ((isalpha(a) == 0) || (isalpha(b) == 0)) {
          printf("ERROR\n");
          break;
        }
          res[toupper(a) - 65][toupper(b) - 65] = 1;
      }
      fclose(fp);
      get_matrix_u(item, res, 0, test);
      printf("Number of paths found: %d\n", num);
      if(num > 0) {
        printf("Length of shortest path: %d\n", min);
      } else {
        printf("No paths found!\n");
      }
      }
      break;
    }
  }
  return 0;
}

// isSafe checks if the next node is a valid path
// Drew heavy inspiration from Darrell Long's code on the Queen's position being safe
bool is_safe(int32_t res[ROWS][COLS], int32_t row, int32_t curr_node) {
  if ((res[curr_node][row] == 1) && (curr_node != row)) {
    return true;
  }
  return false;
}

// Recursive function that goes through every path
bool get_matrix_u(Stack *item, int32_t res[ROWS][COLS], int32_t curr_node, bool test[ROWS]) {
  uint32_t popped_value = 0;
  for (int32_t i = 0; i < 25; i++) {
    if ((is_safe(res, i, curr_node)) && (!test[i])) {
      stack_push(item, curr_node);
      test[curr_node] = true;
      get_matrix_u(item, res, i, test);
      stack_pop(item, &popped_value);					// Backtracks if not valid
      curr_node = popped_value;
      test[curr_node] = false;
    }
  }

  if (res[curr_node][25] == 1) {					// Tells function when 
    stack_print(item);							// it's at the End
    num += 1;
    printf("%c -> %c\n", curr_node + 65, 25 + 65);
    if (stack_size(item) + 2 < min) {
      min = stack_size(item) + 2;
    }
    return true;
  }
  return false;
}

// Prints the Matrix
void print_matrix(int32_t res[][COLS]) {
  int32_t a = 0, b = 0, i_1 = 0, i_2 = 0;
  printf(" ");
  while (i_1 <= 25) {
    printf(" %c", i_1 + 65);
    i_1 += 1;
  }
  printf("\n");
  while (a <= 25) {
    printf("%c ", i_2 + 65);
    while (b <= 25) {
      printf("%d ", res[a][b]);
      b += 1;
    }
    printf("\n");
    i_2 += 1;
    a += 1;
    b = 0;
  }
}
