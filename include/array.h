#ifndef ARRAY_H
#define ARRAY_H

#include <common.h>

#define ARRAY_INIT_CAPACITY 4

typedef struct array array;

#define ARRAY_CREATE(name)                                                     \
  array name;                                                                  \
  array_create(&name)
#define ARRAY_SIZE(array) array_size(&array)
#define ARRAY_EMPTY(array) array_empty(&array)
#define ARRAY_ADD(array, data) array_add(&array, (void *)&data)
#define ARRAY_DELETE(array, index) array_delete(&array, index)
#define ARRAY_SET(array, data, index) array_set(&array, (void *)&data, index)
#define ARRAY_GET(array, index, type) *(type *)array_get(&array, index)
#define ARRAY_TO_STRING(array, print_fmt) array_to_string(&array, print_fmt)
#define ARRAY_CLEANUP(array) array_cleanup(&array)

struct array {
  void **elements;
  size_t size;
  size_t capacity;
};

void array_create(array *arr);
size_t array_size(array *arr) { return arr->size; }
bool array_empty(array *arr) { return arr->size == 0; }
void array_add(array *arr, void *data);
void array_delete(array *arr, size_t index);
void array_set(array *arr, void *data, size_t index);
void *array_get(array *arr, size_t index);
void array_to_string(array *arr,
                     void (*print_fmt)(size_t num_elems, void *data));
void array_cleanup(array *arr);

#endif