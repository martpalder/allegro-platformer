#include <stdio.h>
#include <allegro5/memory.h>
#include <allegro5/bitmap_draw.h>
#include "./hud.h"

Sprite* createHUD(const unsigned char NUM_SPRITES)
{
	Sprite* pSprites = al_malloc(sizeof(Sprite) * NUM_SPRITES);
	if (pSprites == (void*)0)
	{
		fprintf(stderr, "Malloc failed!\n");
		exit(-1);
	}

	unsigned char i;
	for (i = 0; i < NUM_SPRITES; ++i)
	{
		(pSprites + i)->idx = 0;
		(pSprites + i)->x = i * 64;
		(pSprites + i)->y = 0;
	}

	return pSprites;
}

void drawHUD(Sprite* pSprites)
{
	unsigned char i;
	Sprite* pCurrSprt;
	for (i = 0; i < 4; ++i)
	{
		pCurrSprt = pSprites + i;
		al_draw_bitmap_region(
			pCurrSprt->tileset.bitmap,
			(pCurrSprt->tileset.pSources + pCurrSprt->idx)->sx,
			(pCurrSprt->tileset.pSources + pCurrSprt->idx)->sy,
			pCurrSprt->tileset.tileW, pCurrSprt->tileset.tileH,
			pCurrSprt->x, pCurrSprt->y,
			0
		);
	}
}

void destroyHUD(Sprite* pSprites)
{
	al_free(pSprites);
	pSprites = (void*)0;
}
