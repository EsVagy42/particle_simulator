#include "../particle_includes.h"

CREATE_PARTICLE(Sand);

bool swappable_particles[] = {};

void SandInit(Generation *gen, Cell *cell) {
  cell->type = SandParticle;
  *CELL_COLOR(gen, cell->position) = YELLOW;
}

void SandUpdate(Generation *gen, Cell *cell) {
  static Position2 possible_moves[] = {{0, 1}, {1, 1}, {-1, 1}};
  for (Position2 *check_move = possible_moves;
       check_move < ARREND(possible_moves); check_move++) {
    Position2 check_pos = ADD_POS(cell->position, (*check_move));
    if (IS_POS_VALID(gen->size, check_pos)) {
      Cell *check_cell = CELL(gen, check_pos);
      if (check_cell->type < ARRSIZE(swappable_particles) &&
          swappable_particles[check_cell->type]) {
        swap_cells(gen, cell, check_cell);
        *CELL_COLOR(gen, cell->position) = YELLOW;
        break;
      }
    }
  }
}

ADD_PARTICLE(Sand);
