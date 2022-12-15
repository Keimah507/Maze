#ifndef WALL_H
#define WALL_H

#include <math.h>
#include "variables.h"
#include "player.h"
#include "ray.h"
#include "gfx.h"
#include "textures.h"

void	renderWallProjection(void);
void	changeColorIntensity(color_t *color, float factor);

#endif
