#include "indexing.h"
#include "macros.h"
#include "simulator.h"
#include <raylib.h>

int main() {
  const size_t DRAW_RADIUS = 10;

  const Size2 SIMULATOR_SIZE = {400, 300};
  const Size2 WINDOW_SIZE = {800, 600};
  const float PARTICLE_WIDTH =
                  (float)WINDOW_SIZE.width / (float)SIMULATOR_SIZE.width,
              PARTICLE_HEIGHT =
                  (float)WINDOW_SIZE.height / (float)SIMULATOR_SIZE.height;

  Generation generation CLEANUP(Generation) = NEW(Generation, SIMULATOR_SIZE);

  InitWindow(WINDOW_SIZE.width, WINDOW_SIZE.height, "Particle simulator");
  SetTargetFPS(2000);

  while (!WindowShouldClose()) {

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      Index2 mouse_pos = {GetMouseX() / PARTICLE_WIDTH, GetMouseY() / PARTICLE_HEIGHT};

      for (size_t y = mouse_pos.y - DRAW_RADIUS; y < mouse_pos.y + DRAW_RADIUS; y++) {
        for (size_t x = mouse_pos.x - DRAW_RADIUS; x < mouse_pos.x + DRAW_RADIUS; x++) {
          Index2 cell_index = {x, y};
          
          if (!GET_INDEX2_VALID(SIMULATOR_SIZE, cell_index)) {
            continue;
          }
          bool deleting = !IsMouseButtonDown(MOUSE_BUTTON_LEFT);
          GET_CELL((&generation), cell_index)->type = !deleting;
          GET_CELL((&generation), cell_index)->sleeping = deleting;
          if (deleting) {
            GET_CELL((&generation), cell_index)->color = BLACK;
          }
        }
      }
    }

    generate_next_gen(&generation);

    BeginDrawing();
    {
      ClearBackground(BLACK);

      for (size_t y = 0; y < generation.size.height; y++) {
        #pragma unroll 10
        for (size_t x = 0; x < generation.size.width; x++) {
          float particle_pos_x = x * PARTICLE_WIDTH,
                particle_pos_y = y * PARTICLE_HEIGHT;

          Color particle_color = ({
            size_t index = GET_INDEX(generation.size, ((Index2){x, y}));
            IsKeyDown(KEY_SPACE) ? generation.cells[index].color : generation.cell_position[index]->color;
          });
          
          if (!ColorIsEqual(particle_color, BLACK)) {
            DrawRectangle(particle_pos_x, particle_pos_y, PARTICLE_WIDTH,
                          PARTICLE_HEIGHT, particle_color);
          }
        }
      }

      DrawFPS(0, 0);
      if (IsKeyDown(KEY_SPACE)) {
        const char *memory_view_text = "Memory layout view";
        DrawText(memory_view_text, WINDOW_SIZE.width / 2 - MeasureText(memory_view_text, GetFontDefault().baseSize) / 2, 20, GetFontDefault().baseSize, WHITE);
      }
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
