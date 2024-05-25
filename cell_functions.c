#include "cell_functions.h"
#include "macros.h"
#include <stdlib.h>
#include "particles/particles.h"

void (**CELL_UPDATE_FUNCTIONS)(Generation *gen, Cell *cell);

void (**CELL_INIT_FUNCTIONS)(Generation *gen, Cell *cell);

void add_particle(int particle_index,
                  void (*init_func)(Generation *gen, Cell *cell),
                  void (*update_func)(Generation *gen, Cell *cell)) {
  static int current_array_size = 0;

  if (current_array_size == 0) {
    current_array_size = NUM_PARTICLES;
    CELL_UPDATE_FUNCTIONS =
        malloc(current_array_size * sizeof(typeof(*CELL_UPDATE_FUNCTIONS)));
    CELL_INIT_FUNCTIONS =
        malloc(current_array_size * sizeof(typeof(*CELL_INIT_FUNCTIONS)));
  }

  CELL_INIT_FUNCTIONS[particle_index] = init_func;
  CELL_UPDATE_FUNCTIONS[particle_index] = update_func;
}
