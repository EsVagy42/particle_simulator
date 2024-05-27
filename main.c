#include "indexing.h"
#include "io.h"
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
  const Size2 SIMULATOR_SIZE = {300, 200};

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(600, 400, "Particle Simulator V3");
  generation = NEW(Generation, SIMULATOR_SIZE);

  HandleResize(&generation);
  HideCursor();

#if defined(PLATFORMWEB)
  emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  DeleteGeneration(&generation);

  CloseWindow();

  return 0;
}

void UpdateDrawFrame() {
  if (IsWindowResized()) {
    HandleResize(&generation);
  }

  HandleUpdateSelectedIndex();
  HandleUpdateDrawRadius();
  HandleDraw(&generation);

  update_gen(&generation);

  BeginDrawing();
  {
    draw_gen(&generation);
    DrawBrush(&generation);
    DrawFPS(0, 0);
  }
  EndDrawing();
}
