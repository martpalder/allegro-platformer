#pragma once
#ifndef HUD_H
#define HUD_H
#include "./sprite.h"

Sprite* createHUD(const unsigned char NUM_TILES);
void drawHUD(Sprite* pSprites);
void destroyHUD(Sprite* pSprites);

#endif
