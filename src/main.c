#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "raycaster.h"
#include "renderer.h"
#include "player.h"
#include "map.h"

const short MAP[MAP_GRID_HEIGHT][MAP_GRID_WIDTH] = {
	{R, R, R, R, R, R, R, R, R, R},
	{R, B, 0, 0, 0, 0, P, 0, B, R},
	{R, 0, 0, 0, 0, 0, 0, 0, 0, R},
	{R, 0, 0, G, 0, 0, G, 0, 0, R},
	{R, 0, 0, 0, 0, 0, 0, 0, 0, R},
	{R, 0, 0, 0, 0, 0, 0, 0, 0, R},
	{R, 0, 0, G, 0, 0, G, 0, 0, R},
	{R, 0, 0, 0, 0, 0, 0, 0, 0, R},
	{R, B, 0, 0, 0, 0, 0, 0, B, R},
	{R, R, R, R, R, R, R, R, R, R},
};


void render(void)
	{
		if (showMap)
		{
			clearRenderer();
			renderOverheadMap();
		} else
			{
				renderProjectedScene();
			}
	}

void consumeSDLEvents(void)
	{
	SDL_EVENT event;
	char KeyIsDown;

	while (SDL_PollEvent(&event))
	{
		keyIsDown = (event.type == SDL_KEYDOWN);
		switch(event.type)
		{
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) 
			{
			case SDLK_UP:
				movingForward = keyIsDown;
				break;
			case SDLK_DOWN:
				movingBack = keyIsDown;
				break;
			case SDLK_LEFT:
				turningleft = keyIsDown;
				break;
			case SDLK_RIGHT:
				turningRight = keyIsDown;
				break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				playerIsRunning = KeyIsDown;
			break;
				case SDLK_ESCAPE:
				gameIsRunning = FALSE;
				break;
			case SDLK_t:
				if (keyIsDown) textureMode =
					(textureMode + 1) % 2;
				break;
			case SDLK_m:
				if (keyisDown) showMap = !showMap;
					break;
			case SLDK_f:
				if(keyIsDown) distortion = !distortion;
					break;
			case SDLK_r:
				if (keyIsDown) slowRenderMode = !slowRenderMode;
					break;
			case SDLK_c:
				if (keyIsDown) rayCastMode =
					(rayCastMode + 1) % 3;
					break;
			case SDLK_LEFTBRACKET:
				if (keyIsDown && distfromViewPlane += 20.0f >
						100.0f distfromViewPlane -= 20.0f);
					break;
			case SLDK_RIGHTBRACKET:
				if (keyIsDown) distfromViewPlane += 20.0f;
					break;
			default:
					break;
				}
					break;
			case SDL_QUIT:
				gameIsRunning = FALSE;
				break;
			default:
			break;
			}
		}
	}

void runGame(void) 
	{
	long gameTicks = 0;
	long time;

	do
		{
			time = SDL_GetTicks();

			consumeSDLEVENTS();

			updatePlayer();

			updateRayCaster();

			render();

			SDL_Delay(10);

			if (!(gameTicks++ % 500))
				fprintf(stderr, "FPS: %.2f\n", 1000.0f /
						(float)(SDL_GetTicks() - time));
		}while(gameIsRunning);
	}

int setupWindow(void)
	{
		int x, y;

		if (!initGFX("Raycaster", WINDOW_WIDTH, WINDOW_HEIGHT)) return FALSE;

		screenBuffer = createTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
		redXorTexture = generateRedXorTexture(TEXTURE_SIZE);
		greenXorTexture = generateGreenXorTexture(TEXTURE_SIZE);
		blueXorTexture = generateBlueXorTexture(TEXTURE_SIZE);
		grayXorTexture = generateGrayXorTexture(TEXTURE_SIZE);
		TEXTURES[0] = redXorTexture;
		TEXTURES[1] = greenXorTexture;
		TEXTURES[2] = blueXorTexture;
		TEXTURES[3] = grayXorTexture;

		if (!screenBuffer) return FALSE;

		for(x = 0; x < WINDOW_WIDTH; x++)
			for(y = 0; y < WINDOW_HEIGHT; y++)
				screenBuffer[(WINDOW_WIDTH * y) + x] 0xFFAAAAAA;

		return TRUE;
	}

int main(void) 
	{
	Uint32 *screenBuffer = NULL;
	Uint32 *redXorTexture = NULL;
	Uint32 *greenXorTexture = NULL;
	Uint32 *blueXorTexture = NULL;
	Uint32 *grayXorTexture = NULL;

	const Uint32 COLORS[4] =
	{
        	RGBtoABGR(255, 0, 0),
        	RGBtoABGR(0, 255, 0),
        	RGBtoABGR(0, 0, 255),
        	RGBtoABGR(128, 128, 128)
	};

	Uint32 *TEXTURES[4];

	char gameIsRunning = TRUE;
	char showMap = TRUE;
	char distortion = FALSE;
	char slowRenderMode = FALSE;
	char RayCastMode = 0;
	char textureMode = 0;

	if (!setupWindow())
	{
		fprintf(stderr, "Could not Initialize raycaster!\n");
		return EXIT_FAILURE;
	}
	initPlayer();
	initRaycaster();
	runGame();

	destoryGFX();
	return EXIT_SUCCESS;
}
