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
typedef struct sll sll;
struct node {
  void *data;
  unsigned int num_elems;
  int type;
  node *next;
};

struct sll {
  node *head;
  unsigned int size;
};

sll *sll_create_ll(unsigned int num_elems, size_t sizeof_data, void *data,
                   int type);

void sll_cleanup_ll(sll *list);

void sll_push_front(sll *list, unsigned int num_elems, size_t sizeof_data,
                    void *data, int type);
void sll_pop_front(sll *list);
void *front(sll *list);

void sll_push_back(sll *list, unsigned int num_elems, size_t sizeof_data,
                   void *data, int type);
void sll_pop_back(sll *list);
void *back(sll *list);

bool sll_contains(sll *list, void *data, bool (*cmp)(void *d1, void *d2));

void *sll_get(sll *list, void *data, bool (*cmp)(void *d1, void *d2));

void sll_remove(sll *list, void *data, bool (*cmp)(void *d1, void *d2));

unsigned int sll_size(sll *list);

bool sll_empty(sll *list);

void sll_to_string(sll *list,
                   void (*print_fmt)(unsigned int num_elems, void *data));

sll *sll_sort(sll *list, int (*cmp)(void *p_data, void *q_data));

#endif