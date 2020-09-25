#include <slinkedlist.h>

static node *sll_create_node(int num_elems, size_t sizeof_data, void *data,
                             int type);

static size_t size;

node *sll_create_ll(int num_elems, size_t sizeof_data, void *data, int type) {
  size = 0;
  return sll_create_node(num_elems, sizeof_data, data, type);
}

void sll_cleanup_ll(node *head) {
  while (head != NULL) {
    node *tmp = head;
    head = head->next;

    sll_free(tmp);
  }
}

void sll_push_front(node **head, int num_elems, size_t sizeof_data, void *data,
                    int type) {
  node *new_node = sll_create_node(num_elems, sizeof_data, data, type);

  if (*head != NULL) {
    new_node->next = *head;
  }

  *head = new_node;
}

void sll_pop_front(node **head) {
  if (*head != NULL) {
    node *tmp = *head;
    *head = (*head)->next;
    sll_free(tmp);
  }
}

void *front(node *head) { return head != NULL ? head->data : NULL; }

void sll_push_back(node **head, int num_elems, size_t sizeof_data, void *data,
                   int type) {
  node *last_node = *head;

  node *new_node = sll_create_node(num_elems, sizeof_data, data, type);

  if (last_node == NULL) {
    *head = last_node;
  } else {
    while (last_node->next != NULL) {
      last_node = last_node->next;
    }
    last_node->next = new_node;
  }
}

void sll_pop_back(node **head) {
  node *last_node = *head;

  if (last_node != NULL) {
    while (last_node->next->next != NULL) {
      last_node = last_node->next;
    }
    node *tmp = last_node->next;
    last_node->next = NULL;
    sll_free(tmp);
  }
}

void *back(node *head) {
  if (head == NULL) {
    return NULL;
  }

  node *tmp = head;

  while (tmp != NULL) {
    tmp = tmp->next;
  }

  return tmp->data;
}

bool sll_contains(node *head, void *data, bool (*cmp)(void *d1, void *d2)) {
  node *tmp = head;

  while (tmp != NULL) {
    if (cmp(data, tmp->data)) {
      return true;
    }

    tmp = tmp->next;
  }

  return false;
}

size_t sll_size() { return size; }

bool sll_empty() { return size == 0; }

void sll_to_string(node *head,
                   void (*printFmt)(int num_elems, size_t sizeof_data,
                                    void *data)) {

  printf("[dslib - slinked_list]\n");

  printf("[data]: \n");

  node *tmp = head;
  while (tmp != NULL) {
    printFmt(tmp->num_elems, tmp->sizeof_data, tmp->data);

    tmp = tmp->next;
  }

  printf("\n");
}

void sll_free(node *n) {
  free(n->data);
  free(n);
  n = NULL;
}

/* Source:
  https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html

  Define your cmp function so that p->data < q->data returns < 0, p->data ==
  q->data returns 0, and p->data > q->data returns > 0.

*/
node *sll_sort(node *head, int (*cmp)(void *p_data, void *q_data)) {
  node *p, *q, *e, *tail;
  int insize, nmerges, psize, qsize, i;

  if (!head) {
    return NULL;
  }

  insize = 1;

  while (1) {
    p = head;
    head = NULL;
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
          head = e;
        }

        tail = e;
      }

      p = q;
    }

    tail->next = NULL;

    if (nmerges <= 1) {
      return head;
    }

    insize *= 2;
  }
}

static node *sll_create_node(int num_elems, size_t sizeof_data, void *data,
                             int type) {
  node *new_node = malloc(sizeof(node));

  if (new_node != NULL) {

    new_node->data = malloc(sizeof_data * num_elems);

    if (new_node->data != NULL) {

      if (num_elems > 1) {
        void *tmp1 = new_node->data;
        void *tmp2 = data;

        for (int i = 0; i < num_elems * sizeof_data; i += sizeof_data) {
          for (int j = 0; j < sizeof_data; ++j) {
            *((uint8_t *)(tmp1 + j)) = *((uint8_t *)(tmp2 + j));
          }
          tmp1 += sizeof_data;
          tmp2 += sizeof_data;
        }

      } else {

        for (int i = 0; i < sizeof_data; ++i) {
          *((uint8_t *)(new_node->data + i)) = *((uint8_t *)(data + i));
        }
      }

      new_node->num_elems = num_elems;
      new_node->sizeof_data = sizeof_data;
      new_node->type = type;
      new_node->next = NULL;

      size++;
      return new_node;
    }
  }

  return NULL;
}