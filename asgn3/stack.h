#ifndef __STACK_H__
#define __STACK_H__

#include <inttypes.h>
#include <stdbool.h>

#define MIN_STACK 1

typedef uint32_t item;

typedef struct Stack {
  item *entries;
  uint32_t top;
  uint32_t size;
} Stack;

//
// Constructor for a stack.
// A stack is initialized to hold MINIMUM number of uint32_t.
//
// returns: A pointer to the constructed stack.
//
Stack *stack_create(void);

//
// Checks if a stack is empty.
//
// returns: True if the stack is empty, False otherwise.
//
bool stack_empty(Stack *s);

//
// returns: The number of items currently in the stack.
//

uint32_t stack_size(Stack *s);
//
// Pushed an item (a uint32_t) into the stack.
// reutnrs: True if the item was pushed, false otherwise.
//
bool stack_push(Stack *s, uint32_t item);

//
// Pops an item (a uint32_t) off the stack.
// The value of the popped item is stored in the supplied pointer.
// Ex: *item = popped_value
//
// returns: True if the item was popped, false otherwise.
//
bool stack_pop(Stack *s, uint32_t *item);

//
// Function that prints out the contents of a stack.
// Refer to program output for print format.
//
// returns: Void.
//
void stack_print(Stack *s);

// Destructor for Stack
// returns: Void
//
void stack_delete(Stack *s);
#endif
