#ifndef SIMULATOR_STRUCTS_H
#define SIMULATOR_STRUCTS_H

#include "cell_specific_data_size.h"
#include "indexing.h"
#include "properties.h"
#include <assert.h>
#include <raylib.h>
typedef struct {
  Position2 position;
  int type;
  Properties props;
  char data[CELL_DATA_SIZE];
} Cell;

typedef struct {
  Size2 size;
  Cell **cell_position;
  Cell *cells;
  Color *cell_colors;
  Texture2D texture;
  Vector2 cell_graphical_size;
} Generation;

#define CELL_DATA(cell, type) (*(type *)(cell->data))

#define CHECK_CELL_DATA_TYPE(type)                                             \
  static_assert(sizeof(type) <= CELL_DATA_SIZE,                               \
                 "Type too big, consider changing `CELL_DATA_SIZE` in "        \
                 "`cell_specific_data_size.h` to make it fit")

void InitGeneration(Generation *gen, Size2 size);

void DeleteGeneration(Generation *gen);

void CalculateCellGraphicalSize(Generation *gen, Size2 window_size);

#endif
