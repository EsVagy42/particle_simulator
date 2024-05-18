#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "indexing.h"
#include <raylib.h>

#define CELL_DATA_SIZE 0


typedef struct {
  Index2 position;
  Color color;
  size_t type;
  char data[CELL_DATA_SIZE];
} Cell;

typedef struct {
  Cell **cell_position;
  Cell *cells;
  Size2 size;
} Generation;

void init_Generation(Generation *gen, Size2 size);

void free_Generation(Generation *gen);

#define GET_CELL(gen, pos) (gen->cell_position[GET_INDEX(pos)]) 

void swap_cells(Generation *gen, Cell *old_cell, Cell *new_cell);

extern void (*CELL_UPDATE_FUNCTIONS[])(Generation *, Cell *);

void generate_next_gen(Generation *gen);

#endif
