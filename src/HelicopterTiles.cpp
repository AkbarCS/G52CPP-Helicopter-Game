#include "HelicopterTiles.h"

int HelicopterTiles::spacing;

HelicopterTiles::HelicopterTiles() : TileManager(50, 50)
{
}


HelicopterTiles::~HelicopterTiles()
{
}

// Draw a tile at the screen by specifiying the x and y 
// co-ordinates and by specifying which shape to draw
void HelicopterTiles::DrawTileAt(
	BaseEngine* pEngine, 
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{	
	switch (GetValue(iMapX, iMapY))
		{
		case 0:
		case 1:
			pEngine->DrawRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0xff0000,
				pSurface);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			pEngine->DrawRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0xffffff,
				pSurface);
			break;
		}
}

char** HelicopterTiles::updateBackground(char** tileArray)
{
	//height = 12, width = 16 [y][x]

	//shift tile to the left of the array
	char** tmp = 0;
	tmp = new char*[12];
	
	for (int y = 0; y < 12; y++)
		{
		tmp[y] = new char[16];

		for (int x = 1; x < 16; x++)
			{
			tmp[y][x-1] = tileArray[y][x];
			}
		}

	//add new values in the last column
	for (int y2 = 0; y2 < 12; y2++)
		{
		tmp[y2][15] = 'e';
		}

	if (spacing == 6)
		{
		spacing = 0;

		int randomNumber = rand() % 4;

		if (randomNumber == 0)
			{
			tmp[0][15] = 'b'; tmp[1][15] = 'b'; tmp[2][15] = 'b'; tmp[3][15] = 'b'; tmp[4][15] = 'b'; tmp[5][15] = 'b'; tmp[10][15] = 'b'; tmp[11][15] = 'b';
			}
		else if (randomNumber == 1)
			{
			tmp[0][15] = 'b'; tmp[1][15] = 'b'; tmp[2][15] = 'b'; tmp[9][15] = 'b'; tmp[10][15] = 'b'; tmp[11][15] = 'b';
			}
		else if (randomNumber == 2)
			{
			tmp[0][15] = 'b'; tmp[1][15] = 'b'; tmp[6][15] = 'b'; tmp[7][15] = 'b'; tmp[10][15] = 'b'; tmp[11][15] = 'b';
			}
		else
			{
			tmp[0][15] = 'b'; tmp[1][15] = 'b'; tmp[3][15] = 'b'; tmp[6][15] = 'b'; tmp[10][15] = 'b'; tmp[11][15] = 'b';
			}
		}
	else
		{
		tmp[0][15] = 'b'; tmp[1][15] = 'b'; tmp[10][15] = 'b'; tmp[11][15] = 'b';
		spacing++;
		}

	return tmp;
}