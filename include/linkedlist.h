#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <common.h>

typedef struct node node;
typedef struct list list;

#define LL_CREATE(name)                                                        \
  list name;                                                                   \
  ll_create(&name)
#define LL_CLEANUP(list) ll_cleanup(&list)
#define LL_CLEAR(list) ll_clear(&list)
#define LL_PUSH_FRONT(list, num_elems, sizeof_data, data, type)                \
  ll_push_front(&list, num_elems, sizeof_data, (void *)data, type)
#define LL_POP_FRONT(list) ll_pop_front(&list)
#define LL_FRONT(list, type) *(type *)ll_front(&list)
#define LL_PUSH_BACK(list, num_elems, sizeof_data, data, type)                 \
  ll_push_back(&list, num_elems, sizeof_data, (void *)data, type)
#define LL_POP_BACK(list) ll_pop_back(&list)
#define LL_BACK(list, type) *(type *)ll_back(&list)
#define LL_CONTAINS(list, data, cmp) ll_contains(&list, data, cmp)
#define LL_GET(list, data, cmp) ll_get(&list, data, cmp)
#define LL_REMOVE(list, data, cmp) ll_remove(&list, data, cmp)
#define LL_SIZE(list) ll_size(&list)
#define LL_EMPTY(list) ll_empty(&list)
#define LL_TO_STRING(list, print_fmt) ll_to_string(&list, print_fmt)
#define LL_SORT(list, cmp) ll_sort(&list, cmp)

struct node {
  node *prev;
  node *next;
  void *data;
  size_t num_elems;
  int type;
};

struct list {
  node *head;
  node *tail;
  size_t size;
};

void ll_create(list *list);

void ll_cleanup(list *list);

void ll_clear(list *list);

void ll_push_front(list *list, size_t num_elems, size_t sizeof_data, void *data,
                   int type);
void ll_pop_front(list *list);
void *ll_front(list *list);

void ll_push_back(list *list, size_t num_elems, size_t sizeof_data, void *data,
                  int type);
void ll_pop_back(list *list);
void *ll_back(list *list);

bool ll_contains(list *list, void *data, bool (*cmp)(void *d1, void *d2));

node *ll_get(list *list, void *data, bool (*cmp)(void *d1, void *d2));

void ll_remove(list *list, void *data, bool (*cmp)(void *d1, void *d2));

size_t ll_size(list *list);

bool ll_empty(list *list);

void ll_to_string(list *list, void (*print_fmt)(size_t num_elems, void *data));

list *ll_sort(list *list, int (*cmp)(void *p_data, void *q_data));

#endif