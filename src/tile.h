#pragma once
#ifndef TILE_H
#define TILE_H
#include <allegro5/bitmap.h>
#include "./camera.h"

typedef struct {
	unsigned char idx;
	float dx;
	float dy;
} Tile;

typedef struct {
	float sx;
	float sy;
} Source;

typedef struct {
	unsigned char tileW;
	unsigned char tileH;
	short w;
	short h;
	int numTiles;
	Source* pSources;
	ALLEGRO_BITMAP* bitmap;
} Tileset;

typedef struct {
	short mapW;
	short mapH;
	int numTiles;
	Tile* pTiles;
} Tilemap;

Tileset loadTileset(const char* FILEPATH, const unsigned char TILEW, const unsigned char TILEH);
Tilemap loadTilemap(const char* FILEPATH, const unsigned char TILE_SZ);
void destroyTileset(Tileset tset);
void destroyTilemap(Tilemap tmap);
void printTilemapInfo(Tilemap tmap);
void setTile(Tile* pTile, const unsigned char IDX);
void setAllTiles(Tilemap* pTmap, const unsigned char IDX);
void drawTile(Tile* pTile, Tileset* pTset);
void drawTilemap(Tilemap* pTmap, Tileset* pTset, Camera* pCam);

#endif
