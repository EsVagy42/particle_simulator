#include "simulator.h"

#define UPDATE_FUNCTION_COUNT 2

extern void (*PARTICLE_UPDATE_FUNCTIONS[UPDATE_FUNCTION_COUNT]) (Generation *, Cell *);
