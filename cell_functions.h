#ifndef CELL_FUNCTIONS_H
#define CELL_FUNCTIONS_H

#include "simulator_structs.h"

extern void (**CELL_UPDATE_FUNCTIONS)(Generation *gen, Cell *cell);

extern void (**CELL_INIT_FUNCTIONS)(Generation *gen, Cell *cell);

extern char **PARTICLE_NAMES;

extern void add_particle(int particle_index,
                         void (*init_func)(Generation *gen, Cell *cell),
                         void (*update_func)(Generation *gen, Cell *cell),
                         char *name);

#endif
