#include "dynamic_array.h"

void *reallocate(void *pointer, size_t newSize) {
  if (newSize == 0) {
    free(pointer);

    return NULL;
  }

  void *result = realloc(pointer, newSize);

  if (result == NULL) {
    exit(1);
  }

  return result;
}