#ifndef PROPERTIES_H
#define PROPERTIES_H

typedef struct {
  int density;
} Properties;

#define TRY_DENSE_SWAP(gen, cell, positions, valid_cells)                      \
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
      if (!(_cell->props.density == 0) &&                                      \
          cell->props.density <=                                                \
              GetRandomValue(0, cell->props.density + _cell->props.density)) { \
        break;                                                              \
      }                                                                        \
      swap_cells(gen, cell, _cell);                                            \
      break;                                                                   \
    }                                                                          \
  }

#define TRY_DENSE_SWAP_RESULT(gen, cell, positions, valid_cells, result)       \
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
      if (!(_cell->props.density == 0) &&                                      \
          cell->props.density <=                                                \
              GetRandomValue(0, cell->props.density + _cell->props.density)) { \
        break;                                                              \
      }                                                                        \
      swap_cells(gen, cell, _cell);                                            \
      result = true;                                                           \
      break;                                                                   \
    }                                                                          \
  }

#endif
