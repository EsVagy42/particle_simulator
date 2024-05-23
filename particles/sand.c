#include "../particle_includes.h"
#include "particles.h"

CREATE_PARTICLE(Sand);

bool swappable_particles[NUM_PARTICLES] = {[Empty] = true};

void SandInit(Generation *gen, Cell *cell) {
  cell->type = Sand;
  *CELL_COLOR(gen, cell->position) = YELLOW;
}

void SandUpdate(Generation *gen, Cell *cell) {
  static Position2 possible_moves[] = {{0, 1}, {1, 1}, {-1, 1}};
  for (Position2 *move = possible_moves; move < ARREND(possible_moves);
       move++) {
    Position2 cell_pos = ADD_POS(cell->position, (*move));
    if (!IS_POS_VALID(gen->size, cell_pos)) {
      continue;
    }
    Cell *other_cell = CELL(gen, cell_pos);
    if (!swappable_particles[other_cell->type]) {
      continue;
    }
    swap_cells(gen, cell, other_cell);
    *CELL_COLOR(gen, cell->position) = YELLOW;
  }
}

ADD_PARTICLE(Sand);
