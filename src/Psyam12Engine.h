#pragma once

#include "BaseEngine.h"
#include "TileManager.h"
#include "Psyam12TileManager.h"
#include "HelicopterTiles.h"

#include <math.h>       

class TileManager;

class Psyam12Engine :
	public BaseEngine
{ 
protected:
	HelicopterTiles obTileManager;

private:
	int x;
	float object1X;
	float object1Y;
	float object2X;
	float object2Y;

public:
	Psyam12Engine();
	~Psyam12Engine();
	int InitialiseObjects(void);
	void SetupBackgroundBuffer();
	void DrawStrings();
	void DrawString2();
	void UnDrawStrings(int x, int y);
	void DoUpdate(int iCurrentTime);
	void DrawStringsOnTop();
	int collisionDetection(int shape1Radius, int shape2Radius);
};

