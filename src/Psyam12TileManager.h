#pragma once
#include "TileManager.h"
class Psyam12TileManager :
	public TileManager
{
public:
	Psyam12TileManager();
	~Psyam12TileManager();

	void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY, unsigned int colour, int shape) const;

	void DrawAllTilesAt2(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapXStart, int iMapYStart,
		int iMapXEnd, int iMapYEnd,
		int iStartPositionScreenX, int iStartPositionScreenY, unsigned int colour, int shape) const;

};

