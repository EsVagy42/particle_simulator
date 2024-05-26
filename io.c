#include "io.h"
#include "cell_functions.h"
#include "indexing.h"
#include "particles/particles.h"
#include "simulator.h"
#include "simulator_structs.h"
#include <raylib.h>
#include <raymath.h>

int selected_index = 1;

void HandleUpdateSelectedIndex() {
  for (int i = 0; i < 9; i++) {
    if (i == NUM_PARTICLES) {
      break;
    }
    if (IsKeyPressed(KEY_ZERO + i)) {
      selected_index = i;
      break;
    }
  }
}

int draw_radius = 10;

void HandleUpdateDrawRadius() {
  draw_radius += GetMouseWheelMoveV().y;
  draw_radius = Clamp(draw_radius, 0, 50);
}

void HandleDraw(Generation *gen) {
  if (!(IsMouseButtonDown(MOUSE_BUTTON_LEFT) ||
        IsMouseButtonDown(MOUSE_BUTTON_RIGHT))) {
    return;
  }

  Position2 position = {GetMouseX() / gen->cell_graphical_size.x,
                        GetMouseY() / gen->cell_graphical_size.y};
  int particle_index =
      IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? 0 : selected_index;

  for (int y = position.y - draw_radius; y <= position.y + draw_radius; y++) {
    for (int x = position.x - draw_radius; x <= position.x + draw_radius; x++) {
      Position2 cell_pos = {x, y};
      if (!IS_POS_VALID(gen->size, cell_pos)) {
        continue;
      }
      CELL_INIT_FUNCTIONS[particle_index](gen, CELL(gen, cell_pos));
    }
  }
}

void DrawBrush(Generation *gen) {
  Position2 mouse_pos = {GetMouseX(), GetMouseY()};
  DrawRectangleLines(mouse_pos.x - draw_radius * gen->cell_graphical_size.x,
                     mouse_pos.y - draw_radius * gen->cell_graphical_size.y,
                     2 * draw_radius * gen->cell_graphical_size.x,
                     2 * draw_radius * gen->cell_graphical_size.y, WHITE);
  const char *particle_name = PARTICLE_NAMES[selected_index];
  int font_size = GetFontDefault().baseSize;
  Position2 offset = {MeasureText(particle_name, font_size) / 2, font_size / 2};
  DrawText(particle_name, mouse_pos.x - offset.x, mouse_pos.y - offset.y,
           font_size, WHITE);
}

void HandleResize(Generation *gen) {
  Size2 window_size = {GetScreenWidth(), GetScreenHeight()};
  CalculateCellGraphicalSize(gen, window_size);
}
