#include "indexing.h"
#include "macros.h"
#include "simulator.h"
#include "simulator_structs.h"
#include <raylib.h>

#if defined(PLATFORMWEB)
  #include <emscripten/emscripten.h>
#endif

extern void SandInit(Generation *, Cell *);
Generation generation;

void UpdateDrawFrame();

int main() {
  const Size2 SIMULATOR_SIZE = {400, 300};

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "Particle Simulator V3");
  generation = NEW(Generation, SIMULATOR_SIZE);

#if defined(PLATFORMWEB)
  emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  DeleteGeneration(&generation);

  CloseWindow();

  return 0;
}

void UpdateDrawFrame() {
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
