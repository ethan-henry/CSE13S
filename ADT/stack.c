#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Recieved from Slides
// Original Code by: Darrell Long
Stack *stack_create(void) {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->size = MIN_STACK;
  s->top = 0;
  s->entries = (item *)calloc(MIN_STACK, sizeof(item));
  printf("%lu\n", sizeof(s->size));
  return s;
}

bool stack_empty(Stack *s) {
  int x = s->top;
  return x < 0;
}

// Recieved from Slides
// Original Code by: Darell Long
bool stack_push(struct Stack *s, uint32_t item) {
  if (s->top == s->size) {
    s->size *= 2;
    s->entries = (uint32_t *)realloc(s->entries, s->size * sizeof(s));
  }
  s->entries[s->top] = item;
  s->top += 1;
  return true;
}         
                               
bool stack_pop(Stack *s, uint32_t *item) {
  s->top -= 1;
  s->size -= 1;
  *item = s->entries[s->top];
  return s->entries[s->top];
}   
                                                        
void stack_print(Stack *s) { 
  int32_t x = 0;
  int32_t y = s->top;
  while (x < y) { 
    printf("%c ", s->entries[x] + 65);
    x += 1;
  }
}

void stack_delete(Stack *s) {
  s->top = 0;
  free(s);
}

uint32_t stack_size(Stack *s) {
  return s->top;
}
