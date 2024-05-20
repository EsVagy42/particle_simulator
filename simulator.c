#include "simulator.h"
#include "indexing.h"
#include "update_functions.h"
#include <raylib.h>
#include <stdlib.h>

void init_Generation(Generation *gen, Size2 size) {
  size_t items = GET_SIZE(size);
  gen->size = size;
  gen->cells = malloc(items * sizeof(Cell));
  gen->cell_position = malloc(items * sizeof(Cell *));
  for (size_t index = 0; index < items; index++) {
    gen->cells[index] = (Cell){GET_INDEX2(size, index), BLACK, true, 0, {}};
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
  for (size_t i = 0; i < GET_SIZE(gen->size); i++) {
    Cell *current = gen->cells + GetRandomValue(0, GET_SIZE(gen->size) - 1);

    if (current->sleeping) {
      continue;
    }

    void (*current_update_function)(Generation *, Cell *) =
        PARTICLE_UPDATE_FUNCTIONS[current->type];
    if (current_update_function != NULL) {
      current_update_function(gen, current);
    }

    if (!current->sleeping) {
      #pragma unroll 3
      for (size_t y = current->position.y - 1; y <= current->position.y + 1;
           y++) {
        #pragma unroll 3
        for (size_t x = current->position.x - 1; x <= current->position.x + 1;
             x++) {
          Index2 pos = {x, y};
          if (GET_INDEX2_VALID(gen->size, pos)) {
            GET_CELL(gen, pos)->sleeping = false;
          }
        }
      }
    }
  }
}
