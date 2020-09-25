#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <common.h>

typedef struct node node;
typedef struct list list;

struct node {
  node *prev;
  node *next;
  void *data;
  unsigned int num_elems;
  int type;
};

struct list {
  node *head;
  node *tail;
  unsigned int size;
};

list *ll_create_ll();

void ll_cleanup_ll(list *list);

void ll_clear(list *list);

void ll_push_front(list *list, unsigned int num_elems, size_t sizeof_data,
                   void *data, int type);
void ll_pop_front(list *list);
void *ll_front(list *list);

void ll_push_back(list *list, unsigned int num_elems, size_t sizeof_data,
                  void *data, int type);
void ll_pop_back(list *list);
void *ll_back(list *list);

bool ll_contains(list *list, void *data, bool (*cmp)(void *d1, void *d2));

node *ll_get(list *list, void *data, bool (*cmp)(void *d1, void *d2));

void ll_remove(list *list, void *data, bool (*cmp)(void *d1, void *d2));

unsigned int ll_size(list *list);

bool ll_empty(list *list);

void ll_to_string(list *list,
                  void (*print_fmt)(unsigned int num_elems, void *data));

list *ll_sort(list *list, int (*cmp)(void *p_data, void *q_data));

#endif