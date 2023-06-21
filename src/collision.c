#include "./collision.h"

bool isCollisionSprite(Sprite* pSprt1, Sprite* pSprt2)
{
	return (pSprt2->x < pSprt1->x + pSprt1->tileset.tileW
		&& pSprt1->x < pSprt2->x + pSprt2->tileset.tileW)
		&& (pSprt2->y < pSprt1->y + pSprt1->tileset.tileH
		&& pSprt1->y < pSprt2->y + pSprt2->tileset.tileH);
}

bool isCollisionTilemap(Sprite* pSprt, Tilemap* pTmap, Tileset* pTset)
{
	int i;
	Tile* pTile;
	for (i = 0; i < pTmap->numTiles; ++i)
	{
		pTile = pTmap->pTiles + i;
		if (pTile->idx > 0
			&& pTile->dx < pSprt->x + pSprt->tileset.tileW
			&& pSprt->x < pTile->dx + pTset->tileW
			&& pTile->dy < pSprt->y + pSprt->tileset.tileH
			&& pSprt->y < pTile->dy + pTset->tileH)
		{
			return 1;
		}
	}
	return 0;
}
