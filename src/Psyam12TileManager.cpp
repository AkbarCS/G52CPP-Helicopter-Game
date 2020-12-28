#include "Psyam12TileManager.h"


Psyam12TileManager::Psyam12TileManager(void) : TileManager(50, 50)
{
}


Psyam12TileManager::~Psyam12TileManager(void)
{
}

// Draw a tile at the screen by specifiying the x and y 
// co-ordinates and by specifying which shape to draw
void Psyam12TileManager::DrawTileAt(
	BaseEngine* pEngine, 
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY, unsigned int colour, int shape) const
{	
	// Base class implementation just draws some grey tiles
	if (shape == 0)
		{
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			colour,
			pSurface);
		}
	else if (shape == 1)
		{
		pEngine->DrawOval(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			colour,
			pSurface);
		}
}

// Draw all tiles, from start to end position
void Psyam12TileManager::DrawAllTilesAt2(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapXStart, int iMapYStart,
	int iMapXEnd, int iMapYEnd,
	int iStartPositionScreenX, int iStartPositionScreenY, unsigned int colour, int shape) const
{
	for (int iTX = iMapXStart; iTX <= iMapXEnd; iTX++)
		for (int iTY = iMapYStart; iTY <= iMapYEnd; iTY++)
		{
			int iMapX = iStartPositionScreenX + GetTileWidth()*(iTX - iMapXStart);
			int iMapY = GetTileHeight()*(iTY - iMapYStart);

			DrawTileAt(pEngine, pSurface,
				iTX, iTY,
				iMapX,
				iMapY, colour, shape);
		}
}