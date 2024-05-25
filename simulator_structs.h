#ifndef SIMULATOR_STRUCTS_H
#define SIMULATOR_STRUCTS_H

#include "cell_specific_data_size.h"
#include "indexing.h"
#include <raylib.h>
typedef struct {
  Position2 position;
  size_t type;
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

void InitGeneration(Generation *gen, Size2 size);

void DeleteGeneration(Generation *gen);

void CalculateCellGraphicalSize(Generation *gen, Size2 window_size);

#endif
