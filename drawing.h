#ifndef DRAWING_H
#define DRAWING_H

#include "indexing.h"
#include "simulator_structs.h"
#include <raylib.h>
#include <raymath.h>

typedef struct {
  Vector2 particle_size;
  RenderTexture2D texture;
} ParticleDrawer;

void init_ParticleDrawer(ParticleDrawer *pd, Vector2 particle_size,
                         Size2 texture_size);

void free_ParticleDrawer(ParticleDrawer *pd);

void draw_particle(ParticleDrawer *pd, Cell *cell);

#endif
