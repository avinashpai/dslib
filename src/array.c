#include <array.h>

static void array_resize(array *arr, size_t capacity);

void array_create(array *arr, int type) {
  arr->capacity = ARRAY_INIT_CAPACITY;
  arr->size = 0;
  arr->elements = malloc(sizeof(void *) * arr->capacity);
  arr->type = type;
}

void array_set(array *arr, void *data, size_t index) {
  if (index > arr->size) {
    return;
  }

  arr->elements[index] = data;
}

void array_add(array *arr, void *data) {
  if (arr->capacity == arr->size) {
    array_resize(arr, arr->capacity * 2);
  }
  arr->elements[arr->size++] = data;
}

void array_delete(array *arr, size_t index) {
  if (index > arr->size) {
    return;
  }

  arr->elements[index] = NULL;

  for (int i = index; i < arr->size - 1; ++i) {
    arr->elements[i] = arr->elements[i + 1];
    arr->elements[i + 1] = NULL;
  }

  arr->size--;

  if (arr->size > 0 && arr->size == arr->capacity / 4) {
    array_resize(arr, arr->capacity / 2);
  }
}

void *array_get(array *arr, size_t index) {
  if (index > arr->size) {
    return NULL;
  }

  return arr->elements[index];
}

void array_cleanup(array *arr) { free(arr->elements); }

void array_to_string(array *arr,
                     void (*print_fmt)(size_t num_elems, void *data)) {
  printf("[dslib - array]\n");
  printf("[data]: \n");

  for (size_t i = 0; i < arr->size; ++i) {
    print_fmt(1, arr->elements[i]);
  }
  printf("\n");
}

static void array_resize(array *arr, size_t capacity) {
  void **elements = realloc(arr->elements, sizeof(void *) * capacity);
  if (elements) {
    arr->elements = elements;
    arr->capacity = capacity;
  }
}