#ifndef INDEXING_H
#define INDEXING_H

#include <stddef.h>

typedef struct {
  size_t width, height;
} Size2;

typedef struct {
  size_t x, y;
} Position2;

#define GET_LENGTH(size) (size.width * size.height)

#define GET_INDEX(size, position) (position.y * size.width + position.x)

#define IS_POS_VALID(size, position)                                           \
  (position.x >= 0 && position.x < size.width && position.y >= 0 &&            \
   position.y < size.height)

#define ADD_POS(pos0, pos1) ((Position2){pos0.x + pos1.x, pos0.y + pos1.y})

#define SUB_POS(pos0, pos1) ((Position2){pos0.x - pos1.x, pos0.y - pos1.y})

#define GET_POS(size, index)                                                   \
  ((Position2){index % size.width, index / size.width})

#endif
