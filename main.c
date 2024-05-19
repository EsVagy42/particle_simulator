#include "indexing.h"
#include "macros.h"
#include "simulator.h"
#include <raylib.h>

int main() {
  const Size2 SIMULATOR_SIZE = {400, 300};
  const Size2 WINDOW_SIZE = {800, 600};
  const float PARTICLE_WIDTH =
                  (float)WINDOW_SIZE.width / (float)SIMULATOR_SIZE.width,
              PARTICLE_HEIGHT =
                  (float)WINDOW_SIZE.height / (float)SIMULATOR_SIZE.height;

  Generation generation CLEANUP(Generation) = NEW(Generation, SIMULATOR_SIZE);

  InitWindow(WINDOW_SIZE.width, WINDOW_SIZE.height, "Particle simulator");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    GET_CELL((&generation), ((Index2){200, 150}))->type = 1;

    generate_next_gen(&generation);

    BeginDrawing();
    {
      ClearBackground(BLACK);

      for (size_t y = 0; y < generation.size.height; y++) {
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
