#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "indexing.h"
#include "macros.h"
#include "simulator_structs.h"
#define CELL(gen, pos) (*(gen->cell_position + GET_INDEX(gen->size, pos)))

#define CELL_COLOR(gen, pos) (gen->cell_colors + GET_INDEX(gen->size, pos))

void swap_cells(Generation *gen, Cell *current_cell, Cell *other_cell);

void update_gen(Generation *gen);

void draw_gen(Generation *gen);

#define TRY_SWAP(gen, cell, positions, valid_cells)                            \
  {                                                                            \
    for (Position2 *_move = positions; _move < ARREND(positions); _move++) {   \
      Position2 _pos = ADD_POS(cell->position, (*_move));                      \
      if (!IS_POS_VALID(gen->size, _pos)) {                                    \
        continue;                                                              \
      }                                                                        \
      Cell *_cell = CELL(gen, _pos);                                           \
      if (!valid_cells) {                                                      \
        continue;                                                              \
      }                                                                        \
      swap_cells(gen, cell, _cell);                                            \
      break;                                                                   \
    }                                                                          \
  }

#define TRY_SWAP_RESULT(gen, cell, positions, valid_cells, result)             \
  {                                                                            \
    result = false;                                                            \
    for (Position2 *_move = positions; _move < ARREND(positions); _move++) {   \
      Position2 _pos = ADD_POS(cell->position, (*_move));                      \
      if (!IS_POS_VALID(gen->size, _pos)) {                                    \
        continue;                                                              \
      }                                                                        \
      Cell *_cell = CELL(gen, _pos);                                           \
      if (!valid_cells) {                                                      \
        continue;                                                              \
      }                                                                        \
      swap_cells(gen, cell, _cell);                                            \
      result = true;                                                           \
      break;                                                                   \
    }                                                                          \
  }

#define FOR_NEAR(gen, position, positions, statement)                          \
  {                                                                            \
    for (Position2 *_direction = positions; _direction < ARREND(positions);    \
         _direction++) {                                                       \
      Position2 _pos = ADD_POS(position, (*_direction));                       \
      if (!IS_POS_VALID(gen->size, _pos)) {                                    \
        continue;                                                              \
      }                                                                        \
      statement                                                                \
    }                                                                          \
  }

#endif
