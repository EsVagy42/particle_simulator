#include "simulator.h"
#include "indexing.h"
#include <stdlib.h>

void init_Generation(Generation *gen, Size2 size) {
  size_t items = GET_SIZE(size);
  gen->size = size;
  gen->cells = malloc(items * sizeof(Cell));
  gen->cell_position = malloc(items * sizeof(Cell*));
  for (size_t index = 0; index < items; index++) {
    gen->cells[index] = (Cell){GET_INDEX2(size, index), BLACK, 0, {}};
    gen->cell_position[index] = &gen->cells[index];
  }
}

void free_Generation(Generation *gen) {
  free(gen->cell_position);
  free(gen->cells);
}

void swap_cells(Generation *gen, Cell *first_cell, Cell *second_cell) {
  size_t first_index = GET_INDEX(gen->size, first_cell->position);
  size_t second_index = GET_INDEX(gen->size, second_cell->position);
  Index2 first_pos = first_cell->position;
  first_cell->position = second_cell->position;
  second_cell->position = first_pos;
  gen->cell_position[first_index] = second_cell;
  gen->cell_position[second_index] = first_cell;
}

void generate_next_gen(Generation *gen) {
  for (Cell *current = gen->cells; current < gen->cells + sizeof(Cell) * GET_SIZE(gen->size); gen->cells++) {
    void (*current_update_function)(Generation *, Cell *) = CELL_UPDATE_FUNCTIONS[current->type];
    if (current_update_function != NULL) {
      current_update_function(gen, current);
    }
  }
}
