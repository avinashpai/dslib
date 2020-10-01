/*
  Useful Data structures library (dslib) - Singley Linked List (slinked_list)
  Version: v1.0.0
  By: Avinash Pai

  * Head pointer only
  * Usage:
    * create a linked list with sll_create_ll (returns head)
    * insert, delete, etc. using the returned head pointer from the creation
    * all functions that modify the list (push_front, pop_back, etc.) take the
    * head pointer as ** (pass &head_pointer to those functions)
  * Complexity
    * (push_/pop_)front: O(1)
    * (push_/pop_)back/contains: O(n)
    * sort: uses merge sort
      * https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html
      * O(nlogn)
      * provide cmp function pointer with comparision function for node data
  * Misc.
    * sll_contains, sll_get, sll_remove, sll_to_string, and sll_sort only work
    *  if all the nodes contain values of the same type
    * to use these functions provide them with a pointer to a function that
    *  defines the comparison or print format for the desired type
    * type member is of type int and can be used along with enums to indentify
    *  the type
*/
#ifndef SLINKED_LIST_H
#define SLINKED_LIST_H
#include <common.h>

typedef struct node node;
typedef struct slist slist;

#define SLL_CREATE(name)                                                       \
  slist name;                                                                  \
  sll_create(&name)
#define SLL_CLEANUP(list) sll_cleanup(&list)
#define SLL_CLEAR(list) sll_clear(&list)
#define SLL_PUSH_FRONT(list, num_elems, sizeof_data, data, type)               \
  sll_push_front(&list, num_elems, sizeof_data, (void *)&data, type)
#define SLL_POP_FRONT(list) sll_pop_front(&list)
#define SLL_FRONT(list, type) *(type *)sll_front(&list)
#define SLL_PUSH_BACK(list, num_elems, sizeof_data, data, type)                \
  sll_push_back(&list, num_elems, sizeof_data, (void *)&data, type)
#define SLL_POP_BACK(list) sll_pop_back(&list)
#define SLL_BACK(list, type) *(type *)sll_back(&list)
#define SLL_CONTAINS(list, data, cmp) sll_contains(&list, (void *)&data, cmp)
#define SLL_GET(list, data, cmp) sll_get(&list, (void *)&data, cmp)
#define SLL_REMOVE(list, data, cmp) sll_remove(&list, (void *)&data, cmp)
#define SLL_SIZE(list) sll_size(&list)
#define SLL_EMPTY(list) sll_empty(&list)
#define SLL_TO_STRING(list, print_fmt) sll_to_string(&list, print_fmt)
#define SLL_SORT(list, cmp) *sll_sort(&list, cmp)

struct node {
  void *data;
  size_t num_elems;
  int type;
  node *next;
};

struct slist {
  node *head;
  size_t size;
};

void sll_create(slist *list);

void sll_cleanup(slist *list);

void sll_clear(slist *list);

void sll_push_front(slist *list, size_t num_elems, size_t sizeof_data,
                    void *data, int type);
void sll_pop_front(slist *list);
void *sll_front(slist *list);

void sll_push_back(slist *list, size_t num_elems, size_t sizeof_data,
                   void *data, int type);
void sll_pop_back(slist *list);
void *sll_back(slist *list);

bool sll_contains(slist *list, void *data, bool (*cmp)(void *d1, void *d2));

node *sll_get(slist *list, void *data, bool (*cmp)(void *d1, void *d2));

void sll_remove(slist *list, void *data, bool (*cmp)(void *d1, void *d2));

size_t sll_size(slist *list);

bool sll_empty(slist *list);

void sll_to_string(slist *list,
                   void (*print_fmt)(size_t num_elems, void *data));

slist *sll_sort(slist *list, int (*cmp)(void *p_data, void *q_data));

#endif