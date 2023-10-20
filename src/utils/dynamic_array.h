#ifndef dynamic_array_h
#define dynamic_array_h

#include <stdlib.h>

#define Array(T) struct{ T* data; unsigned int count; unsigned int capacity;}

#define initArray(array) \
  do { \
    array.count = 0; \
    array.capacity = 0; \
    array.data = NULL; \
  } while (0);

#define destroyArray(array) \
  do { \
    reallocate(array.data, 0); \
    initArray(array); \
  } while (0);

#define pushToArray(array, value) \
  do { \
    if (array.capacity < array.count + 1) { \
      unsigned int oldCapacity = array.capacity; \
      array.capacity = oldCapacity < 8 ? 8 : (unsigned int)((oldCapacity) * 1.5); \
      array.data = reallocate(array.data, sizeof(*array.data) * (array.capacity)); \
    } \
    array.data[array.count] = value; \
    array.count++; \
  } while (0);

void *reallocate(void *, size_t);

#endif /* dynamic_array_h */
