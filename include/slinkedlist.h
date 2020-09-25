/*
  Useful Data structures library (dslib) - Singley Linked List (slinked_list)
  Version: v1.0.0
  By: Avinash Pai

  - Head pointer only
  - Usage:
    - create a linked list with sll_create_ll (returns head)
    - insert, delete, etc. using the returned head pointer from the creation
    - all functions that modify the list (push_front, pop_back, etc.) take the
      head pointer as ** (pass &head_pointer to those functions)
  - Complexity
    - (push_/pop_)front: O(1)
    - (push_/pop_)back/contains: O(n)
    - sort: uses merge sort
      - https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html
      - O(nlogn)
      - provide cmp function pointer with comparision function for node data
  - Misc.
    - sll_contains, sll_get, sll_remove, sll_to_string, and sll_sort only work
  if all the nodes contain values of the same type
    - to use these functions provide them with a pointer to a function that
      defines the comparison or print format for the desired type
*/
#ifndef SLINKED_LIST_H
#define SLINKED_LIST_H
#include <common.h>

typedef struct node node;

struct node {
  void *data;
  int num_elems;
  int type;
  node *next;
};

node *sll_create_ll(int num_elems, size_t sizeof_data, void *data, int type);

void sll_cleanup_ll(node *head);

void sll_push_front(node **head, int num_elems, size_t sizeof_data, void *data,
                    int type);
void sll_pop_front(node **head);
void *front(node *head);

void sll_push_back(node **head, int num_elems, size_t sizeof_data, void *data,
                   int type);
void sll_pop_back(node **head);
void *back(node *head);

bool sll_contains(node *head, void *data, bool (*cmp)(void *d1, void *d2));

void *sll_get(node *head, void *data, bool (*cmp)(void *d1, void *d2));

void sll_remove(node *head, void *data, bool (*cmp)(void *d1, void *d2));

size_t sll_size();

bool sll_empty();

void sll_to_string(node *head, void (*print_fmt)(int num_elems, void *data));

void sll_free(node *n);

node *sll_sort(node *head, int (*cmp)(void *p_data, void *q_data));

#endif