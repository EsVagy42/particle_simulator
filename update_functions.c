#include "update_functions.h"
#include "particles/empty.c"
#include "particles/sand.c"

void (*PARTICLE_UPDATE_FUNCTIONS[UPDATE_FUNCTION_COUNT]) (Generation *, Cell *) = {
  [Empty] = NULL,
  [Sand] = update_sand,
};
