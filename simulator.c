#include "simulator.h"
#include "cell_functions.h"
#include "indexing.h"
#include "simulator_structs.h"
#include <raylib.h>

void swap_cells(Generation *gen, Cell *current_cell, Cell *other_cell) {
  Position2 other_position = other_cell->position;
  int other_index = GET_INDEX(gen->size, other_position);
  int current_index = GET_INDEX(gen->size, current_cell->position);
  gen->cell_colors[current_index] = gen->cell_colors[other_index];
  other_cell->position = current_cell->position;
  current_cell->position = other_position;
  gen->cell_position[other_index] = current_cell;
  gen->cell_position[current_index] = other_cell;
}

void update_gen(Generation *gen) {
  const int GENERATION_LENGTH = GET_LENGTH(gen->size);
  for (int i = 0; i < GENERATION_LENGTH; i++) {
    Cell *current = gen->cells + GetRandomValue(0, GENERATION_LENGTH - 1);

    void (*update_function)(Generation *, Cell *) =
        CELL_UPDATE_FUNCTIONS[current->type];

    if (update_function != NULL) {
      update_function(gen, current);
    }
  }
}

void draw_gen(Generation *gen) {
  Image image = {
    .data = gen->cell_colors,
    .width = gen->size.width,
    .height = gen->size.height,
    .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
    .mipmaps = 1,
  };

  UnloadTexture(gen->texture);
  gen->texture = LoadTextureFromImage(image);

  Size2 window_size = {GetScreenWidth(), GetScreenHeight()};
  DrawTexturePro(gen->texture, (Rectangle){0, 0, gen->size.width, gen->size.height}, (Rectangle){0, 0, window_size.width, window_size.height}, (Vector2){0., 0.}, 0., WHITE);
}
