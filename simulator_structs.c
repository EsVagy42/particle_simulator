#include "simulator_structs.h"
#include "indexing.h"
#include "particles/particles.h"
#include <stdlib.h>

void InitGeneration(Generation *gen, Size2 size) {
  size_t items = GET_LENGTH(size);

  gen->size = size;
  gen->cells = malloc(items * sizeof(Cell));
  gen->cell_position = malloc(items * sizeof(Cell *));
  gen->cell_colors = malloc(items * sizeof(Color));

  for (size_t i = 0; i < items; i++) {
    gen->cells[i] = (Cell){GET_POS(size, i), Empty, {}};
    gen->cell_position[i] = &gen->cells[i];
    gen->cell_colors[i] = BLACK;
  }
}

void DeleteGeneration(Generation *gen) {
  free(gen->cell_position);
  free(gen->cells);
  free(gen->cell_colors);
}
