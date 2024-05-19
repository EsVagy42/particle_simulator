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
  Index2 swap_cell_index[] = {{cell->position.x, cell->position.y + 1},
                              {cell->position.x - 1, cell->position.y + 1},
                              {cell->position.x + 1, cell->position.y + 1}};
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
  }

  cell->color = YELLOW;
}
