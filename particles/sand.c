#ifndef SAND_PARTICLE_H
#define SNAD_PARTICLE_H

#include "../simulator.h"
#include "../update_functions.h"
#include "empty.c"
#include <raylib.h>
#include "../macros.h"

#define Sand 1

const bool SWAPPABLE_CELL_TYPES[UPDATE_FUNCTION_COUNT] = {
    [Empty] = true,
};

void update_sand(Generation *gen, Cell *cell) {
  Cell *swap_cell = NULL;

  int random_direction = GetRandomValue(0, 1) * 2 - 1;
  Index2 swap_cell_index[] = {{cell->position.x, cell->position.y + 1},
                              {cell->position.x - random_direction, cell->position.y + 1},
                              {cell->position.x + random_direction, cell->position.y + 1}};
  for (Index2 *test_index = swap_cell_index;
       test_index < swap_cell_index + ARR_SIZE(swap_cell_index); test_index++) {
    if (GET_INDEX2_VALID(gen->size, (*test_index))) {
      Cell *test_cell = GET_CELL(gen, (*test_index));
      if (SWAPPABLE_CELL_TYPES[test_cell->type]) {
        swap_cell = test_cell;
        break;
      }
    }
  }

  if (swap_cell != NULL) {
    swap_cells(gen, swap_cell, cell);
  } else {
    cell->sleeping = true;
  }

  cell->color = YELLOW;
}

#endif
