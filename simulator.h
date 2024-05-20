#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "indexing.h"
#include <raylib.h>
#include "cell_data_size.h"
#include "simulator_structs.h"
#include "drawing.h"

#define GET_CELL(gen, pos) (gen->cell_position[GET_INDEX(gen->size, pos)]) 

void swap_cells(Generation *gen, Cell *old_cell, Cell *new_cell);

void generate_next_gen(Generation *gen, ParticleDrawer *pd);

void awake_neighbours(Generation *gen, Cell *cell);

#endif
