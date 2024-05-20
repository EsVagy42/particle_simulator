#include "simulator.h"
#include "indexing.h"
#include "macros.h"
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

void awake_neighbours(Generation *gen, Cell *cell) {
#pragma unroll 3
  for (size_t y = cell->position.y - 1; y <= cell->position.y + 1; y++) {
#pragma unroll 3
    for (size_t x = cell->position.x - 1; x <= cell->position.x + 1; x++) {
      Index2 pos = {x, y};
      if (GET_INDEX2_VALID(gen->size, pos)) {
        GET_CELL(gen, pos)->sleeping = false;
      }
    }
  }
}

void awake_range(Generation *gen, Cell *cell0, Cell *cell1) {
  Index2 minimum = {MIN(cell0->position.x, cell1->position.x),
                    MIN(cell0->position.y, cell1->position.y)};
  Index2 maximum = {MAX(cell0->position.x, cell1->position.x),
                    MAX(cell0->position.y, cell1->position.y)};

  for (size_t y = minimum.y - 1; y <= maximum.y + 1; y++) {
    for (size_t x = minimum.x - 1; x <= maximum.x + 1; x++) {
      Index2 pos = {x, y};
      if (GET_INDEX2_VALID(gen->size, pos)) {
        GET_CELL(gen, pos)->sleeping = false;
      }
    }
  }
}

void swap_cells(Generation *gen, Cell *first_cell, Cell *second_cell) {
  size_t first_index = GET_INDEX(gen->size, first_cell->position);
  size_t second_index = GET_INDEX(gen->size, second_cell->position);
  Index2 first_pos = first_cell->position;
  first_cell->position = second_cell->position;
  second_cell->position = first_pos;
  gen->cell_position[first_index] = second_cell;
  gen->cell_position[second_index] = first_cell;

  awake_range(gen, first_cell, second_cell);
}

void generate_next_gen(Generation *gen, ParticleDrawer *pd) {
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

    draw_particle(pd, current);
  }
}
