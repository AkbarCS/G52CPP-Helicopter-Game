#pragma once
#include "TileManager.h"
class HelicopterTiles :
	public TileManager
{
public:
	HelicopterTiles();
	~HelicopterTiles();

	void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;

	static char** HelicopterTiles::updateBackground(char** tileArray);

private:
	static int spacing;
};

