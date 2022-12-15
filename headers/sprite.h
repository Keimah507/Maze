#ifndef SPRITE_H
#define SPRITE_H

#include "variables.h"
#include "gfx.h"
#include "player.h"
#include "textures.h"

typedef struct
{
	float	x;
	float	y;
	float	distance;
	float	angle;
	bool	visible;
	int		texture;
}	sprite_t;

void	renderSpriteProjection(void);
void	renderMapSprites(void);

#endif
