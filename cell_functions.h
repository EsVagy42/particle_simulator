#ifndef CELL_FUNCTIONS_H
#define CELL_FUNCTIONS_H

#include "simulator_structs.h"
#define CELL_COUNT 0

extern void (*CELL_UPDATE_FUNCTIONS[CELL_COUNT])(Generation *gen, Cell *cell);

extern void (*CELL_INIT_FUNCTIONS[CELL_COUNT])(Generation *gen, Cell *cell);

#endif
