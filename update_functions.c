#include "update_functions.h"

void (*PARTICLE_UPDATE_FUNCTIONS[]) (Generation *, Cell *) = {
  NULL,
};
