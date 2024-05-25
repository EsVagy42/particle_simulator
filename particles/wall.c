#include "../particle_includes.h"

CREATE_PARTICLE(Wall);

void WallInit(Generation *gen, Cell *cell) {
  cell->type = Wall;
  *CELL_COLOR(gen, cell->position) = GRAY;
}

ADD_PARTICLE(Wall);
