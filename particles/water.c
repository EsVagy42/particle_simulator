#include "../particle_includes.h"
#include "particles.h"
#include <raylib.h>

CREATE_PARTICLE(Water);

bool water_swappable_particles[NUM_PARTICLES] = {[Empty] = true};
bool water_slideable_particles[NUM_PARTICLES] = {[Empty] = true};

typedef struct {
  bool sliding_right;
} WaterStruct;
CHECK_CELL_DATA_TYPE(WaterStruct);

void WaterInit(Generation *gen, Cell *cell) {
  cell->type = Water;
  CELL_DATA(cell, WaterStruct).sliding_right = GetRandomValue(0, 1);
  *CELL_COLOR(gen, cell->position) = BLUE;
}

void WaterUpdate(Generation *gen, Cell *cell) {
  {
    Position2 below_pos = ADD_POS(cell->position, ((Position2){0, 1}));
    if (!IS_POS_VALID(gen->size, below_pos)) {
      goto SLIDE;
    }
    Cell *other = CELL(gen, below_pos);
    if (!water_swappable_particles[other->type]) {
      goto SLIDE;
    }
    swap_cells(gen, cell, other);
    *CELL_COLOR(gen, cell->position) = BLUE;
    return;
  }

SLIDE:
  static Position2 possible_slides[] = {{-1, 0}, {1, 0}};
  Position2 slide_pos =
      ADD_POS(cell->position,
              possible_slides[CELL_DATA(cell, WaterStruct).sliding_right]);
  if (!IS_POS_VALID(gen->size, slide_pos)) {
    CELL_DATA(cell, WaterStruct).sliding_right =
        !CELL_DATA(cell, WaterStruct).sliding_right;
    return;
  }
  Cell *other = CELL(gen, slide_pos);
  if (other->type == Water) {
    if (CELL_DATA(cell, WaterStruct).sliding_right !=
        CELL_DATA(other, WaterStruct).sliding_right) {
      swap_cells(gen, cell, other);
      *CELL_COLOR(gen, cell->position) = BLUE;
    } else {
      CELL_DATA(cell, WaterStruct).sliding_right =
          !CELL_DATA(cell, WaterStruct).sliding_right;
    }
    return;
  }
  if (water_slideable_particles[other->type]) {
    swap_cells(gen, cell, other);
    *CELL_COLOR(gen, cell->position) = BLUE;
  } else {
    CELL_DATA(cell, WaterStruct).sliding_right =
        !CELL_DATA(cell, WaterStruct).sliding_right;
  }
}

ADD_PARTICLE(Water);
