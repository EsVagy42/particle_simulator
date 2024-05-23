#include "cell_functions.h"
#include <stdlib.h>

void (**CELL_UPDATE_FUNCTIONS)(Generation *gen, Cell *cell);

void (**CELL_INIT_FUNCTIONS)(Generation *gen, Cell *cell);

size_t add_particle(void (*init_func)(Generation *gen, Cell *cell),
                    void (*update_func)(Generation *gen, Cell *cell)) {
  static size_t current_particle_index = 0;
  static size_t current_array_size = 0;

  if (current_particle_index == current_array_size) {
    if (current_array_size == 0) {
      current_array_size = 2;
      CELL_UPDATE_FUNCTIONS =
          malloc(current_array_size * sizeof(typeof(*CELL_UPDATE_FUNCTIONS)));
      CELL_INIT_FUNCTIONS =
          malloc(current_array_size * sizeof(typeof(*CELL_INIT_FUNCTIONS)));
    } else {
      current_array_size *= 2;
      CELL_UPDATE_FUNCTIONS =
          realloc(CELL_UPDATE_FUNCTIONS,
                  current_array_size * sizeof(typeof(*CELL_UPDATE_FUNCTIONS)));
      CELL_INIT_FUNCTIONS =
          realloc(CELL_INIT_FUNCTIONS,
                  current_array_size * sizeof(typeof(*CELL_INIT_FUNCTIONS)));
    }

    CELL_UPDATE_FUNCTIONS[current_particle_index] = init_func;
    CELL_INIT_FUNCTIONS[current_particle_index] = update_func;
    current_particle_index++;
  }
}
