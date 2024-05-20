#include "drawing.h"
#include <raylib.h>

void draw_particle(ParticleDrawer *pd, Cell *cell) {
  DrawRectangle(pd->particle_size.x * cell->position.x,
                pd->particle_size.y * cell->position.y, pd->particle_size.x,
                pd->particle_size.y, cell->color);
};

void init_ParticleDrawer(ParticleDrawer *pd, Vector2 particle_size,
                         Size2 texture_size) {
  pd->particle_size = particle_size;
  pd->texture = LoadRenderTexture(texture_size.width, texture_size.height);
}

void free_ParticleDrawer(ParticleDrawer *pd) {
  UnloadRenderTexture(pd->texture);
}
