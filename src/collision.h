#pragma once
#ifndef COLLISION_H
#define COLLISION_H
#include "./sprite.h"
#include "./tile.h"

bool isCollisionSprite(Sprite* pSprt1, Sprite* pSprt2);
bool isCollisionTilemap(Sprite* pSprt, Tilemap* pTmap, Tileset* pTset);

#endif
