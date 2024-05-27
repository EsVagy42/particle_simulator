#include "../particle_includes.h"

CREATE_PARTICLE(Sand);

bool sand_swappable_particles[NUM_PARTICLES] = {
    [Empty] = true, [Water] = true};

void SandInit(Generation *gen, Cell *cell) {
  cell->type = Sand;
  *CELL_COLOR(gen, cell->position) = YELLOW;
}

void SandUpdate(Generation *gen, Cell *cell) {
  static Position2 possible_moves[] = {{0, 1}, {1, 1}, {-1, 1}};
  TRY_SWAP(gen, cell, possible_moves, sand_swappable_particles[_cell->type]);
  *CELL_COLOR(gen, cell->position) = YELLOW;
}

ADD_PARTICLE(Sand);
