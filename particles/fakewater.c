#include "../particle_includes.h"
#include "particles.h"
#include <raylib.h>

CREATE_PARTICLE(FakeWater)

bool fwater_swappable_particles[NUM_PARTICLES] = {[Empty] = true};

typedef struct {
  bool sliding_right;
} FWaterStruct;
CHECK_CELL_DATA_TYPE(FWaterStruct);

void FakeWaterInit(Generation *gen, Cell *cell) {
  cell->type = FakeWater;
  CELL_DATA(cell, FWaterStruct).sliding_right = GetRandomValue(0, 1);
  *CELL_COLOR(gen, cell->position) = SKYBLUE;
}

void FakeWaterUpdate(Generation *gen, Cell *cell) {
  for (int i = 0; i < 128; i++) {
    static Position2 possible_moves_arr[2][3] = {{{0, 1}, {-1, 1}, {-1, 0}},
                                                 {{0, 1}, {1, 1}, {1, 0}}};
    Position2 *possible_moves =
        possible_moves_arr[CELL_DATA(cell, FWaterStruct).sliding_right];
    for (Position2 *move = possible_moves; move < possible_moves + 3; move++) {
      Position2 cell_pos = ADD_POS(cell->position, (*move));
      if (!IS_POS_VALID(gen->size, cell_pos)) {
        continue;
      }
      Cell *other_cell = CELL(gen, cell_pos);
      if (!fwater_swappable_particles[other_cell->type]) {
        continue;
      }
      swap_cells(gen, cell, other_cell);
      goto CHECK;
    }
    CELL_DATA(cell, FWaterStruct).sliding_right =
        !CELL_DATA(cell, FWaterStruct).sliding_right;
    *CELL_COLOR(gen, cell->position) = SKYBLUE;
    return;

  CHECK:
    Position2 bottom_pos = ADD_POS(cell->position, ((Position2){0, 1}));
    if (!IS_POS_VALID(gen->size, bottom_pos)) {
      *CELL_COLOR(gen, cell->position) = SKYBLUE;
      return;
    }
    Cell *bottom_cell = CELL(gen, bottom_pos);
    if (bottom_cell->type != FakeWater) {
      *CELL_COLOR(gen, cell->position) = SKYBLUE;
      return;
    }
  }
}

ADD_PARTICLE(FakeWater)
