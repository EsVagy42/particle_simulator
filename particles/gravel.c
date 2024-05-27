#include "../particle_includes.h"
#include "particles.h"

CREATE_PARTICLE(Gravel)

bool gravel_swappable_particles[NUM_PARTICLES] = {
    [Empty] = true, [Water] = true};

void GravelInit(Generation *gen, Cell *cell) {
  cell->type = Gravel;
  *CELL_COLOR(gen, cell->position) = GRAY;
}

int GRAVEL_MAX_FALL = 3;

void GravelUpdate(Generation *gen, Cell *cell) {
  Position2 position_arr[] = {{0, 1}};
  for (int i = 0; i < GRAVEL_MAX_FALL; i++) {
    bool swap_success;
    TRY_SWAP_RESULT(gen, cell, position_arr,
                    gravel_swappable_particles[_cell->type], swap_success);
    if (!swap_success) {
      break;
    }
  }
  *CELL_COLOR(gen, cell->position) = GRAY;
}

ADD_PARTICLE(Gravel)
