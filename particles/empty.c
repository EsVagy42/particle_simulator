#include "../particle_includes.h"
#include <raylib.h>

CREATE_PARTICLE(Empty);

void EmptyInit(Generation *gen, Cell *cell) {
  cell->type = Empty;
  cell->props = (Properties){.density =  0};
  *CELL_COLOR(gen, cell->position) = BLACK;
}

ADD_PARTICLE(Empty);
