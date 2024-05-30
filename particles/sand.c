#include "../particle_includes.h"

CREATE_PARTICLE(Sand);

bool sand_swappable_particles[NUM_PARTICLES] = {[Empty] = true, [Water] = true};

void SandInit(Generation *gen, Cell *cell) {
  cell->type = Sand;
  cell->props = (Properties){.density = 10};
  *CELL_COLOR(gen, cell->position) = YELLOW;
}

int MAX_FALL = 4;

void SandUpdate(Generation *gen, Cell *cell) {
  static Position2 possible_moves[2][3] = {{{0, 1}, {1, 1}, {-1, 1}},
                                           {{0, 1}, {-1, 1}, {1, 1}}};
  bool polarity = GetRandomValue(0, 1);
  for (int i = 0; i < MAX_FALL; i++) {
    bool swap_success;
    TRY_DENSE_SWAP_RESULT(gen, cell, possible_moves[polarity],
                    sand_swappable_particles[_cell->type], swap_success);

    if (!swap_success) {
      break;
    }
  }
  *CELL_COLOR(gen, cell->position) = YELLOW;
}

ADD_PARTICLE(Sand);
