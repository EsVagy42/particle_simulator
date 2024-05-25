#include "cell_functions.h"
#include "macros.h"
#include "particles/particles.h"
#include <stdlib.h>

void (**CELL_UPDATE_FUNCTIONS)(Generation *gen, Cell *cell);

void (**CELL_INIT_FUNCTIONS)(Generation *gen, Cell *cell);

char **PARTICLE_NAMES;

void add_particle(int particle_index,
                  void (*init_func)(Generation *gen, Cell *cell),
                  void (*update_func)(Generation *gen, Cell *cell),
                  char *name) {
  static int current_array_size = 0;

  if (current_array_size == 0) {
    current_array_size = NUM_PARTICLES;
    CELL_UPDATE_FUNCTIONS =
        malloc(current_array_size * sizeof(typeof(*CELL_UPDATE_FUNCTIONS)));
    CELL_INIT_FUNCTIONS =
        malloc(current_array_size * sizeof(typeof(*CELL_INIT_FUNCTIONS)));
    PARTICLE_NAMES = malloc(current_array_size * sizeof(char *));
  }

  CELL_INIT_FUNCTIONS[particle_index] = init_func;
  CELL_UPDATE_FUNCTIONS[particle_index] = update_func;
  PARTICLE_NAMES[particle_index] = name;
}
