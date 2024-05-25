#ifndef IO_H
#define IO_H

#include "simulator_structs.h"
#include <stddef.h>

extern size_t selected_index;

void HandleUpdateSelectedIndex();

extern int draw_radius;

void HandleUpdateDrawRadius();

void HandleDraw(Generation *gen);

void HandleResize(Generation *gen);

#endif
