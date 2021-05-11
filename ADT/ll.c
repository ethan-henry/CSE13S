#include "ll.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern bool move_to_front;
extern uint32_t num_link;
extern uint32_t num_search;

ListNode *ll_node_create(GoodSpeak *gs) {
  ListNode *n = (ListNode *)malloc(sizeof(ListNode));
  if (n) {
    n->gs = gs_create(gs->oldspeak, gs->newspeak);
  }
  return n;
}

void ll_node_delete(ListNode *n) {
  if (n) {
    if (n->gs) {
      gs_delete(n->gs);
    }
    free(n);
    n = NULL;
  }
  return;
}

void ll_delete(ListNode *head) {
  if (head) {
    ListNode *p = head;
    while (p != NULL) {
      ListNode *r = p;
      p = p->next;
      ll_node_delete(r);
    }
    free(p);
    p = NULL;
  }
  return;
}

GoodSpeak *ll_node_gs(ListNode *n) { return n->gs; }

ListNode *ll_insert(ListNode **head, GoodSpeak *gs) {
  if ((ll_lookup(head, gs->oldspeak) != NULL) && (*head != NULL)) {
    return *head;
  }

  ListNode *output = ll_node_create(gs);
  output->next = (*head);
  (*head) = output;
  return *head;
}

ListNode *ll_lookup(ListNode **head, char *key) {
  num_search += 1;
  ListNode *h = *head;
  ListNode *prev = NULL;
  if (*head && key) {
    while ((h != NULL) && (strcmp(h->gs->oldspeak, key) != 0)) {
      prev = h;
      h = h->next;
      num_link += 1;
    }
    ListNode *output = h;
    if (output != NULL) {
      if ((move_to_front) && (prev != NULL) && (output != *head) && (output->next != NULL)) {
        prev->next = output->next;
        output->next = (*head);
        (*head) = output;
      } 
    }
    return output;
  }
  return NULL;
}

void ll_node_print(ListNode *n) {
  if (n) {
    printf("%s\n", n->gs->oldspeak);
  }
  return;
}

void ll_print(ListNode *head) {
  while (head->next != NULL) {
    printf("%s", head->gs->oldspeak);
    head = head->next;
  }
  printf("\n");
  return;
}
