#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include <allegro5/bitmap.h>
#include "./camera.h"
#include "./tile.h"

typedef struct {
	unsigned char idx;
	float x;
	float y;
	Tileset tileset;
} Sprite;

Sprite createSprite(const char* FILEPATH, const int X, const int Y, const uint8_t TILEW, const uint8_t TILEH);
void destroySprite(Sprite* pSprt);
void setSpritePos(Sprite* pSprt, const float X, const float Y);
void moveSpriteLeft(Sprite* pSprt, const float MOVE_STEP);
void moveSpriteRight(Sprite* pSprt, const float MOVE_STEP);
void moveSpriteUp(Sprite* pSprt, const float MOVE_STEP);
void moveSpriteDown(Sprite* pSprt, const float MOVE_STEP);
void drawSprite(Sprite* pSprt, Camera* pCam, ALLEGRO_BITMAP* bitmap);
void drawSpriteRegion(Sprite* pSprt, Camera* pCam);

#endif
