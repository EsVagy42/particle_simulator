#ifndef PARTICLE_INCLUDES_H
#define PARTICLE_INCLUDES_H

#include <raylib.h>
#include "macros.h"
#include "indexing.h"
#include "simulator_structs.h"
#include "simulator.h"
#include "cell_functions.h"
#include "particles/particles.h"

#define CREATE_PARTICLE(name) \
  void __attribute__((weak)) name##Init(Generation *gen, Cell *cell); \
  void __attribute__((weak)) name##Update(Generation *gen, Cell *cell); \

#define ADD_PARTICLE(name) \
  __attribute__((constructor)) \
  void Add##name##Particle() { \
    add_particle( \
      name, \
      name##Init ? &name##Init : NULL, \
      name##Update ? &name##Update : NULL); \
  }
#endif
