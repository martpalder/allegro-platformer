#include <stdio.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/bitmap_draw.h>
#include "./sprite.h"

Sprite createSprite(const char* FILEPATH, const int X, const int Y, const uint8_t TILEW, const uint8_t TILEH)
{
	Sprite sprt;
	sprt.idx = 0;
	sprt.x = X;
	sprt.y = Y;
	sprt.tileset = loadTileset(FILEPATH, TILEW, TILEH);

	return sprt;
}

void destroySprite(Sprite* pSprt)
{
	destroyTileset(pSprt->tileset);
}

void setSpritePos(Sprite* pSprt, const float X, const float Y)
{
	pSprt->x = X;
	pSprt->y = Y;
}

void moveSpriteLeft(Sprite* pSprt, const float MOVE_STEP)
{
	pSprt->x -= MOVE_STEP;
}

void moveSpriteRight(Sprite* pSprt, const float MOVE_STEP)
{
	pSprt->x += MOVE_STEP;
}

void moveSpriteUp(Sprite* pSprt, const float MOVE_STEP)
{
	pSprt->y -= MOVE_STEP;
}

void moveSpriteDown(Sprite* pSprt, const float MOVE_STEP)
{
	pSprt->y += MOVE_STEP;
}

void drawSprite(Sprite* pSprt, Camera* pCam, ALLEGRO_BITMAP* bitmap)
{
	al_draw_bitmap(
		bitmap,
		pSprt->x - pCam->x,
		pSprt->y - pCam->y,
		0
	);
}

void drawSpriteRegion(Sprite* pSprt, Camera* pCam)
{
	Source* pSrc;
	pSrc = pSprt->tileset.pSources + pSprt->idx;
	al_draw_bitmap_region(
		pSprt->tileset.bitmap,
		pSrc->sx, pSrc->sy,
		pSprt->tileset.tileW,
		pSprt->tileset.tileH,
		pSprt->x - pCam->x,
		pSprt->y - pCam->y,
		0
	);
}
