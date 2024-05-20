#include "drawing.h"
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

  InitWindow(WINDOW_SIZE.width, WINDOW_SIZE.height, "Particle simulator");

  ParticleDrawer drawer CLEANUP(ParticleDrawer) =
      NEW(ParticleDrawer, ((Vector2){PARTICLE_WIDTH, PARTICLE_HEIGHT}),
          WINDOW_SIZE);

  Generation generation CLEANUP(Generation) = NEW(Generation, SIMULATOR_SIZE);

  while (!WindowShouldClose()) {

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) ||
        IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      bool deleting = !IsMouseButtonDown(MOUSE_BUTTON_LEFT);
      Index2 mouse_pos = {GetMouseX() / PARTICLE_WIDTH,
                          GetMouseY() / PARTICLE_HEIGHT};

      for (size_t y = mouse_pos.y - DRAW_RADIUS; y < mouse_pos.y + DRAW_RADIUS;
           y++) {
        for (size_t x = mouse_pos.x - DRAW_RADIUS;
             x < mouse_pos.x + DRAW_RADIUS; x++) {
          Index2 cell_index = {x, y};

          if (!GET_INDEX2_VALID(SIMULATOR_SIZE, cell_index)) {
            continue;
          }
          GET_CELL((&generation), cell_index)->type = !deleting;
          GET_CELL((&generation), cell_index)->sleeping = deleting;
          if (deleting) {
            GET_CELL((&generation), cell_index)->color = BLACK;
          }
        }
      }
    }

    BeginTextureMode(drawer.texture);
    { generate_next_gen(&generation, &drawer); }
    EndTextureMode();

    BeginDrawing();
    {
      ClearBackground(BLACK);
      DrawTextureRec(drawer.texture.texture,
                     (Rectangle){0, 0, drawer.texture.texture.width,
                                 -drawer.texture.texture.height},
                     (Vector2){0., 0.}, WHITE);
      DrawFPS(0, 0);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
