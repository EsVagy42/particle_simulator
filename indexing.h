#ifndef INDEXING_H
#define INDEXING_H

#include <stddef.h>

struct Size2 {
  size_t width, height;
};

struct Index2 {
  size_t x, y;
};

#define GET_INDEX(size, index) (index.y * size.width + index.x)

#define GET_INDEX2(size, index)                                                \
  ((Index2){index % size.width, index / size.width})

#define GET_SIZE(size) (size.width * size.height)

#define GET_INDEX2_VALID(size, index)                                          \
  (index.x >= 0 && index.x < size.width && index.y >= 0 &&                     \
   index.y < size.height)

#endif
