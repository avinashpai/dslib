#include <slinkedlist.h>

static node *sll_create_node(unsigned int num_elems, size_t sizeof_data,
                             void *data, int type);
static void sll_free(node *n);

slist *sll_create_ll() {
  slist *new_sll = malloc(sizeof(slist));
  new_sll->head = NULL;
  new_sll->size = 0;
  return new_sll;
}

void sll_cleanup_ll(slist *list) {
  while (list->head != NULL) {
    node *tmp = list->head;
    list->head = list->head->next;

    sll_free(tmp);
  }
  free(list);
  list = NULL;
}

void sll_clear(slist *list) {
  sll_cleanup_ll(list);
  list = sll_create_ll();
}

void sll_push_front(slist *list, unsigned int num_elems, size_t sizeof_data,
                    void *data, int type) {
  node *new_node = sll_create_node(num_elems, sizeof_data, data, type);
  list->size++;

  if (list->head != NULL) {
    new_node->next = list->head;
  }

  list->head = new_node;
}

void sll_pop_front(slist *list) {
  if (list->head != NULL) {
    node *tmp = list->head;
    list->head = list->head->next;
    sll_free(tmp);
    list->size--;
  }
}

void *front(slist *list) {
  return list->head != NULL ? list->head->data : NULL;
}

void sll_push_back(slist *list, unsigned int num_elems, size_t sizeof_data,
                   void *data, int type) {
  node *last_node = list->head;

  node *new_node = sll_create_node(num_elems, sizeof_data, data, type);
  list->size++;

  if (last_node == NULL) {
    list->head = last_node;
  } else {
    while (last_node->next != NULL) {
      last_node = last_node->next;
    }
    last_node->next = new_node;
  }
}

void sll_pop_back(slist *list) {
  node *last_node = list->head;

  if (last_node != NULL) {
    while (last_node->next->next != NULL) {
      last_node = last_node->next;
    }
    node *tmp = last_node->next;
    last_node->next = NULL;
    sll_free(tmp);
    list->size--;
  }
}

void *back(slist *list) {
  if (list->head == NULL) {
    return NULL;
  }

  node *tmp = list->head;

  while (tmp != NULL) {
    tmp = tmp->next;
  }

  return tmp->data;
}

bool sll_contains(slist *list, void *data, bool (*cmp)(void *d1, void *d2)) {
  node *tmp = list->head;

  while (tmp != NULL) {
    if (cmp(data, tmp->data)) {
      return true;
    }

    tmp = tmp->next;
  }

  return false;
}

node *sll_get(slist *list, void *data, bool (*cmp)(void *d1, void *d2)) {
  node *tmp = list->head;

  while (tmp != NULL) {
    if (cmp(data, tmp->data)) {
      return tmp;
    }

    tmp = tmp->next;
  }

  return NULL;
}

void sll_remove(slist *list, void *data, bool (*cmp)(void *d1, void *d2)) {
  node *tmp = list->head;
  node *prev = tmp;

  while (tmp != NULL) {
    if (cmp(data, tmp->data)) {
      prev->next = tmp->next;
      sll_free(tmp);
      list->size--;
    }

    prev = tmp;
    tmp = tmp->next;
  }
}

unsigned int sll_size(slist *list) { return list->size; }

bool sll_empty(slist *list) { return list->size == 0; }

void sll_to_string(slist *list,
                   void (*print_fmt)(unsigned int num_elems, void *data)) {

  printf("[dslib - slinked_list]\n");

  printf("[data]: \n");

  node *tmp = list->head;
  while (tmp != NULL) {
    print_fmt(tmp->num_elems, tmp->data);

    tmp = tmp->next;
  }

  printf("\n");
}

/* Source:
  https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html

  Define your cmp function so that p->data < q->data returns < 0, p->data ==
  q->data returns 0, and p->data > q->data returns > 0.

*/
slist *sll_sort(slist *list, int (*cmp)(void *p_data, void *q_data)) {
  node *p, *q, *e, *tail;
  int insize, nmerges, psize, qsize, i;

  if (!list->head) {
    return NULL;
  }

  insize = 1;

  while (1) {
    p = list->head;
    list->head = NULL;
    tail = NULL;

    nmerges = 0;

    while (p) {
      nmerges++;
      q = p;
      psize = 0;
      for (i = 0; i < insize; ++i) {
        psize++;
        q = q->next;
        if (!q) {
          break;
        }
      }

      qsize = insize;

      while (psize > 0 || (qsize > 0 && q)) {
        if (psize == 0) {
          e = q;
          q = q->next;
          qsize--;
        } else if (qsize == 0 || !q) {
          e = p;
          p = p->next;
          psize--;
        } else if (cmp(p->data, q->data) <= 0) {
          e = p;
          p = p->next;
          psize--;
        } else {
          e = q;
          q = q->next;
          qsize--;
        }

        if (tail) {
          tail->next = e;
        } else {
          list->head = e;
        }

        tail = e;
      }

      p = q;
    }

    tail->next = NULL;

    if (nmerges <= 1) {
      return list;
    }

    insize *= 2;
  }
}

static node *sll_create_node(unsigned int num_elems, size_t sizeof_data,
                             void *data, int type) {
  node *new_node = malloc(sizeof(node));

  if (new_node != NULL) {

    new_node->data = malloc(sizeof_data * num_elems);

    if (new_node->data != NULL) {

      if (num_elems > 1) {
        void *tmp1 = new_node->data;
        void *tmp2 = data;

        for (size_t i = 0; i < num_elems * sizeof_data; i += sizeof_data) {
          for (size_t j = 0; j < sizeof_data; ++j) {
            *((uint8_t *)(tmp1 + j)) = *((uint8_t *)(tmp2 + j));
          }
          tmp1 += sizeof_data;
          tmp2 += sizeof_data;
        }

      } else {

        for (size_t i = 0; i < sizeof_data; ++i) {
          *((uint8_t *)(new_node->data + i)) = *((uint8_t *)(data + i));
        }
      }

      new_node->num_elems = num_elems;
      new_node->type = type;
      new_node->next = NULL;

      return new_node;
    }
  }

  return NULL;
}

static void sll_free(node *n) {
  free(n->data);
  free(n);
  n = NULL;
}