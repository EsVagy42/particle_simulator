#include "../particle_includes.h"
#include <raylib.h>

CREATE_PARTICLE(Water)

bool water_swappable_particles[NUM_PARTICLES] = {[Empty] = true, [Sand] = true};
const int LOOP_COUNT = 400;
const int FALL_BEFORE_RETURN = 3;

typedef struct {
  bool sliding_right;
} WaterStruct;
CHECK_CELL_DATA_TYPE(WaterStruct);

void WaterInit(Generation *gen, Cell *cell) {
  cell->type = Water;
  cell->props = (Properties){.density = 2};
  CELL_DATA(cell, WaterStruct).sliding_right = GetRandomValue(0, 1);
  *CELL_COLOR(gen, cell->position) = SKYBLUE;
}

void WaterUpdate(Generation *gen, Cell *cell) {
  int fall_count = FALL_BEFORE_RETURN;
  for (int i = 0; i < LOOP_COUNT; i++) {
    static Position2 possible_moves_arr[2][3] = {{{0, 1}, {-1, 1}, {-1, 0}},
                                                 {{0, 1}, {1, 1}, {1, 0}}};
    bool swap_success;
    TRY_DENSE_SWAP_RESULT(
        gen, cell,
        possible_moves_arr[CELL_DATA(cell, WaterStruct).sliding_right],
        water_swappable_particles[_cell->type], swap_success);

    if (!swap_success) {
      CELL_DATA(cell, WaterStruct).sliding_right =
          !CELL_DATA(cell, WaterStruct).sliding_right;
      *CELL_COLOR(gen, cell->position) = BLUE;
      return;
    }

    Position2 bottom_pos = ADD_POS(cell->position, ((Position2){0, 1}));
    if (!IS_POS_VALID(gen->size, bottom_pos)) {
      *CELL_COLOR(gen, cell->position) = SKYBLUE;
      return;
    }
    Cell *bottom_cell = CELL(gen, bottom_pos);
    if (bottom_cell->type == Empty) {
      if (fall_count != 0) {
        fall_count--;
        continue;
      }
      *CELL_COLOR(gen, cell->position) = SKYBLUE;
      return;
    }
  }
  *CELL_COLOR(gen, cell->position) = SKYBLUE;
}

ADD_PARTICLE(Water)
