#include <linkedlist.h>

static ll_node *ll_create_node(size_t num_elems, size_t sizeof_data, void *data,
                               int type);
static void ll_free(ll_node *n);

void ll_create(list *list) {
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void ll_cleanup(list *list) {
  while (list->head != NULL) {
    ll_node *tmp = list->head;
    list->head = list->head->next;

    ll_free(tmp);
  }
}

void ll_clear(list *list) {
  ll_cleanup(list);
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void ll_push_front(list *list, size_t num_elems, size_t sizeof_data, void *data,
                   int type) {
  ll_node *new_node = ll_create_node(num_elems, sizeof_data, data, type);
  list->size++;

  if (list->head != NULL) {
    new_node->next = list->head;
    list->head->prev = new_node;
  }

  list->head = new_node;
}

void ll_pop_front(list *list) {
  if (list->head != NULL) {
    ll_node *tmp = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    ll_free(tmp);
    list->size--;
  }
}

void *ll_front(list *list) {
  return list->head != NULL ? list->head->data : NULL;
}

void ll_push_back(list *list, size_t num_elems, size_t sizeof_data, void *data,
                  int type) {
  ll_node *new_node = ll_create_node(num_elems, sizeof_data, data, type);
  list->size++;

  if (list->head == NULL) {
    list->head = new_node;
  } else {
    if (list->tail == NULL) {
      list->head->next = new_node;
      new_node->prev = list->head;
    } else {
      new_node->prev = list->tail;
      list->tail->next = new_node;
    }
  }

  list->tail = new_node;
}

void ll_pop_back(list *list) {
  if (list->head != NULL) {
    if (list->tail == NULL) {
      ll_free(list->head);
    } else {
      ll_node *tmp = list->tail;
      list->tail->prev->next = NULL;
      list->tail = list->tail->prev;
      ll_free(tmp);
    }
    list->size--;
  }
}

void *ll_back(list *list) {
  if (list->head != NULL) {
    if (list->tail == NULL) {
      return list->head->data;
    } else {
      return list->tail->data;
    }
  } else {
    return NULL;
  }
}

bool ll_contains(list *list, void *data, bool (*cmp)(void *, void *)) {
  ll_node *tmp = list->head;
  while (tmp != NULL) {
    if (cmp(data, tmp->data)) {
      return true;
    }
    tmp = tmp->next;
  }
  return false;
}

ll_node *ll_get(list *list, void *data, bool (*cmp)(void *, void *)) {
  ll_node *tmp = list->head;
  while (tmp != NULL) {
    if (cmp(data, tmp->data)) {
      return tmp;
    }
    tmp = tmp->next;
  }
  return NULL;
}

void ll_remove(list *list, void *data, bool (*cmp)(void *, void *)) {
  ll_node *tmp = list->head;

  while (tmp != NULL) {
    if (cmp(data, tmp->data)) {
      if (tmp->prev == NULL) {
        list->head = tmp->next;
      } else {
        tmp->prev->next = tmp->next;
      }
      ll_free(tmp);
      list->size--;
    }
    tmp = tmp->next;
  }
}

size_t ll_size(list *list) { return list->size; }

bool ll_empty(list *list) { return list->size == 0; }

void ll_to_string(list *list, void (*print_fmt)(size_t, void *)) {
  printf("[dslib - linked_list]\n");

  printf("[data]: \n");

  ll_node *tmp = list->head;
  while (tmp != NULL) {
    print_fmt(tmp->num_elems, tmp->data);

    tmp = tmp->next;
  }
  printf("\n");
}

// TODO: FIX LIST SORTING
list *ll_sort(list *list, int (*cmp)(void *, void *)) {
  ll_node *p, *q, *e, *tail;
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
        } else if (cmp(p, q) <= 0) {
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
        e->prev = tail;

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

static ll_node *ll_create_node(size_t num_elems, size_t sizeof_data, void *data,
                               int type) {
  ll_node *new_node = malloc(sizeof(ll_node));

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
      new_node->prev = NULL;
      new_node->next = NULL;

      return new_node;
    }
  }

  return NULL;
}

static void ll_free(ll_node *n) {
  free(n->data);
  free(n);
  n = NULL;
}
