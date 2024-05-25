#ifndef PARTICLE_INCLUDES_H
#define PARTICLE_INCLUDES_H

#include "cell_functions.h"
#include "indexing.h"
#include "macros.h"
#include "particles/particles.h"
#include "simulator.h"
#include "simulator_structs.h"
#include <raylib.h>

#define CREATE_PARTICLE(name)                                                  \
  void __attribute__((weak)) name##Init(Generation *gen, Cell *cell);          \
  void __attribute__((weak)) name##Update(Generation *gen, Cell *cell);        \
  char* name##ParticleName = #name;

#define ADD_PARTICLE(name)                                                     \
  __attribute__((constructor)) void Add##name##Particle() {                    \
    add_particle(name, (name##Init ? &name##Init : NULL),                      \
                 (name##Update ? &name##Update : NULL), name##ParticleName);   \
  }
#endif
