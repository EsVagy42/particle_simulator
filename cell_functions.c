#include "cell_functions.h"

void (*CELL_UPDATE_FUNCTIONS[CELL_COUNT])(Generation *gen, Cell *cell) = {
  
};

void (*CELL_INIT_FUNCTIONS[CELL_COUNT])(Generation *gen, Cell *cell) = {
  
};
