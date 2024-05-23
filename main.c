#include "indexing.h"
#include "macros.h"
#include "simulator.h"
#include "simulator_structs.h"
#include <raylib.h>

extern void SandInit(Generation *, Cell *);

int main() {
  const Size2 SIMULATOR_SIZE = {400, 300};

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "Particle Simulator V3");
  Generation generation AUTODEL(Generation) = NEW(Generation, SIMULATOR_SIZE);

  while (!WindowShouldClose()) {
    SandInit(&generation, CELL((&generation), ((Position2){200, 50})));
    
    update_gen(&generation);
    
    BeginDrawing();
    {
      ClearBackground(WHITE);
      draw_gen(&generation);
      DrawFPS(0, 0);
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
