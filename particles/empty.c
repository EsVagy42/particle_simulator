#include "../particle_includes.h"

CREATE_PARTICLE(Empty);

void EmptyInit(Generation *gen, Cell *cell) {
  cell->type = Empty;
}

ADD_PARTICLE(Empty);
