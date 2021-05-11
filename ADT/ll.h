#ifndef __LL_H__
#define __LL_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include <stdbool.h>

extern bool move_to_front;

typedef struct ListNode ListNode;

typedef struct GoodSpeak {
  char *oldspeak;
  char *newspeak;
} GoodSpeak;

struct ListNode {
  GoodSpeak *gs;
  ListNode *next;
};

ListNode *ll_node_create(GoodSpeak *gs);

void ll_node_delete(ListNode *n);

void ll_delete(ListNode *head);

ListNode *ll_insert(ListNode **head, GoodSpeak *gs);

ListNode *ll_lookup(ListNode **head, char *key);

#endif
