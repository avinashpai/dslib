#include <linkedlist.h>

typedef enum { INT, FLOAT, FLOAT_ARR, CHAR, STRING, STRUCT } type;

bool cmpInts(void *d1, void *d2) { return *(int *)d1 == *(int *)d2; }

void float_arr_print_fmt(size_t length, void *data) {
  printf("  [");
  for (size_t i = 0; i < length * sizeof(float); i += sizeof(float)) {
    printf(" (%f) ", *(float *)(data + i));
  }
  printf("]\n");
}

void int_print_fmt(size_t length, void *data) {
  printf("  [%d]\n", *(int *)data);
}

int int_cmp(void *p_data, void *q_data) {
  return *(int *)p_data - *(int *)q_data;
}

int main(int argc, char **argv) {
  int n1 = 524;
  int n2 = 134;
  int n3 = 65;

  float arr1[3] = {1.f, 2.f, 3.f};
  float arr2[3] = {4.f, 5.f, 6.f};
  float arr3[3] = {7.f, 8.f, 9.f};

  LL_CREATE(ll1);
  LL_PUSH_FRONT(ll1, 3, sizeof(float), arr2, FLOAT_ARR);
  LL_PUSH_FRONT(ll1, 3, sizeof(float), arr1, FLOAT_ARR);

  LL_CREATE(ll2);
  LL_PUSH_FRONT(ll2, 1, sizeof(int), &n3, INT);
  LL_PUSH_FRONT(ll2, 1, sizeof(int), &n2, INT);
  LL_PUSH_FRONT(ll2, 1, sizeof(int), &n1, INT);

  LL_TO_STRING(ll1, float_arr_print_fmt);
  LL_TO_STRING(ll2, int_print_fmt);
  list ll2_sorted = LL_SORT(ll2, int_cmp);
  printf("SORTED: \n");
  LL_TO_STRING(ll2_sorted, int_print_fmt);

  printf("ll1 size: %zu\n", ll_size(&ll1));
  printf("ll2 size: %zu\n", ll_size(&ll2));

  printf("ll1 empty? %s\n", ll_empty(&ll1) ? "true" : "false");
  printf("ll2 empty? %s\n", ll_empty(&ll2) ? "true" : "false");

  LL_CLEANUP(ll1);
  LL_CLEANUP(ll2);

  return 0;
}
