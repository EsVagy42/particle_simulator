#include "io.h"
#include "cell_functions.h"
#include "indexing.h"
#include "particles/particles.h"
#include "simulator.h"
#include "simulator_structs.h"
#include <raylib.h>
#include <raymath.h>
#include "simulator_structs.h"

size_t selected_index = 1;

void HandleUpdateSelectedIndex() {
  for (size_t i = 0; i < 9; i++) {
    if (i == NUM_PARTICLES) {
      break;
    }
    if (IsKeyPressed(KEY_ZERO + i)) {
      selected_index = i;
      break;
    }
  }
}

int draw_radius = 1;

void HandleUpdateDrawRadius() {
  draw_radius += GetMouseWheelMoveV().y;
  draw_radius = Clamp(draw_radius, 1, 50);
}

void HandleDraw(Generation *gen) {
  if (!(IsMouseButtonDown(MOUSE_BUTTON_LEFT) ||
        IsMouseButtonDown(MOUSE_BUTTON_RIGHT))) {
    return;
  }
  Position2 position = {GetMouseX() / gen->cell_graphical_size.x, GetMouseY() / gen->cell_graphical_size.y};
  size_t particle_index =
      IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? 0 : selected_index;

  for (int y = position.y - draw_radius; y <= position.y + draw_radius;
       y++) {
    for (int x = position.x - draw_radius; x <= position.x + draw_radius; x++) {
      Position2 cell_pos = {x, y};
      if (!IS_POS_VALID(gen->size, cell_pos)) {
        continue;
      }
      CELL_INIT_FUNCTIONS[particle_index](gen, CELL(gen, cell_pos));
    }
  }
}

void HandleResize(Generation *gen) {
  Size2 window_size = {GetScreenWidth(), GetScreenHeight()};
  CalculateCellGraphicalSize(gen, window_size);
}
