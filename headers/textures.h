#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>
#include "variables.h"
#include "upng.h"

upng_t	*textures[NUM_TEXTURES];

void	loadTextures();
void	freeTextures();

#endif
