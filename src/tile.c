#include <stdio.h>
#include <string.h>
#include <allegro5/memory.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/bitmap_draw.h>
#include "./tile.h"

Tileset loadTileset(const char* FILEPATH, const unsigned char TILEW, const unsigned char TILEH)
{
	Tileset tset;
	int sx, sy;
	unsigned short i, j, idx;

	/// Load a bitmap
	tset.bitmap = al_load_bitmap(FILEPATH);
	if (tset.bitmap == (void*)0)
	{
		fprintf(stderr, "Failed to load a bitmap: '%s'!\n", FILEPATH);
		exit(-1);
	}

	// Set tile size
	tset.tileW = TILEW;
	tset.tileH = TILEH;

	// Set tileset dimensions (in tiles)
	tset.w = al_get_bitmap_width(tset.bitmap) / TILEW;
	tset.h = al_get_bitmap_height(tset.bitmap) / TILEH;

	// Set number of tiles
	tset.numTiles = tset.w * tset.h;
	
	// Allocate memory for tileset sources
	tset.pSources = (Source*)al_malloc(sizeof(Source) * tset.numTiles);
	if (tset.pSources == (void*)0)
	{
		fprintf(stderr, "Malloc failed!\n");
		exit(-1);
	}

	// Set tileset sources
	idx = 0;
	for (i = 0; i < tset.h; ++i)
	{
		for (j = 0; j < tset.w; ++j)
		{
			sx = j * TILEW;
			sy = i * TILEH;
			*(tset.pSources + idx++) = (Source){ sx, sy };
		}
	}

	return tset;
}

Tilemap loadTilemap(const char* FILEPATH, const unsigned char TILE_SZ)
{
	Tilemap tmap;
	ALLEGRO_FILE* fp;
	int64_t fSize;
	char line[32];
	char c;
	char* charBuff;
	int i, j, idx;

	// Open a tilemap file
	fp = al_fopen(FILEPATH, "r");
	if (fp == (void*)0)
	{
		fprintf(stderr, "Failed to open a tilemap: '%s'!\n", FILEPATH);
		exit(-1);
	}

	// Get map file size
	al_fseek(fp, 0, SEEK_END);
	fSize = al_ftell(fp);
	al_fseek(fp, 0, SEEK_SET);

	// Allocate character buffer
	charBuff = (char*)al_malloc(fSize);

	// Read the tilemap file
	tmap.mapW = 0;
	tmap.mapH = 0;
	idx = 0;
	while (al_fgets(fp, line, 32) != NULL)
	{
		// Set tilemap width
		if (!tmap.mapW)
		{
			tmap.mapW = (int)strcspn(line, "\n");
		}

		// Get characters
		for (i = 0; i < tmap.mapW; ++i)
		{
			c = *(line + i);
			*(charBuff + idx++) = c;
			//putc(c, stdout);
		}

		// Increase tilemap height
		++tmap.mapH;
		//putc('\n', stdout);
	}

	// Set number of map tiles
	tmap.numTiles = tmap.mapW * tmap.mapH;

	// Close the tilemap file
	al_fclose(fp);
	fp = (void*)0;

	// Allocate memory for tilemap tiles
	tmap.pTiles = (Tile*)al_malloc(sizeof(Tile) * tmap.numTiles);
	if (tmap.pTiles == (void*)0)
	{
		fprintf(stderr, "Malloc failed!\n");
		exit(-1);
	}

	// Set tilemap tiles
	idx = 0;
	for (i = 0; i < tmap.mapH; ++i)
	{
		for (j = 0; j < tmap.mapW; ++j)
		{
			c = *(charBuff + idx);
			*(tmap.pTiles + idx++) = (Tile){ c - 48, j * TILE_SZ, i * TILE_SZ};
			//putc(c, stdout);
		}
		//putc('\n', stdout);
	}

	// Free character buffer
	al_free(charBuff);
	charBuff = (void*)0;

	return tmap;
}

void destroyTileset(Tileset tset)
{
	al_destroy_bitmap(tset.bitmap);
	tset.bitmap = (void*)0;
	al_free(tset.pSources);
	tset.pSources = (void*)0;
}

void destroyTilemap(Tilemap tmap)
{
	al_free(tmap.pTiles);
	tmap.pTiles = (void*)0;
}

void printTilemapInfo(Tilemap tmap)
{
	// Print tilemap size
	printf("Map width: %d\nMap height: %d\n", tmap.mapW, tmap.mapH);
}

void setTile(Tile* pTile, const unsigned char IDX)
{
	// Set the tile index
	pTile->idx = IDX;
}

void setAllTiles(Tilemap* pTmap, const unsigned char IDX)
{
	Tile* pTile;
	unsigned short i, j, idx;

	idx = 0;
	for (i = 0; i < pTmap->mapH; ++i)
	{
		for (j = 0; j < pTmap->mapW; ++j)
		{
			// Get a tilemap tile
			pTile = (pTmap->pTiles + idx++);

			// Set the tile index
			pTile->idx = IDX;
		}
	}
}

void drawTile(Tile* pTile, Tileset* pTset)
{
	al_draw_bitmap_region(
		pTset->bitmap,
		pTset->pSources->sx, pTset->pSources->sy,
		pTset->tileW, pTset->tileH,
		pTile->dx, pTile->dy,
		0
	);
}

void drawTilemap(Tilemap* pTmap, Tileset* pTset, Camera* pCam)
{
	Tile* pTile;
	unsigned short i, j, idx;

	idx = 0;
	for (i = 0; i < pTmap->mapH; ++i)
	{
		for (j = 0; j < pTmap->mapW; ++j)
		{
			// Get a tilemap tile
			pTile = (pTmap->pTiles + idx++);
			if (pTile->idx > pTset->numTiles - 1)
			{
				pTile->idx = pTset->numTiles - 1;
			}

			// Draw the tile
			al_draw_bitmap_region(
				pTset->bitmap,
				(pTset->pSources + pTile->idx)->sx,
				(pTset->pSources + pTile->idx)->sy,
				pTset->tileW, pTset->tileH,
				pTile->dx - pCam->x,
				pTile->dy - pCam->y,
				0
			);
		}
	}
}
