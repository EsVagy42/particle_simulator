#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "simulator_structs.h"
#define CELL(gen, pos) (gen->cell_position + GET_INDEX(gen->size, pos))

#define CELL_COLOR(gen, pos) (gen->cell_colors + GET_INDEX(gen->size, pos))

void swap_cells(Generation *gen, Cell *current_cell, Cell *other_cell);

void update_gen(Generation *gen);

void draw_gen(Generation *gen);

#endif
