#pragma once

#include "DisplayableObject.h"
#include "MovementPosition.h"

//class TileManager;

class Psyam12DisplayableObject1 :
	public DisplayableObject
{
public:
	Psyam12DisplayableObject1(BaseEngine* pEngine);
	~Psyam12DisplayableObject1();
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	void SetMovement(int iStartTime, int iEndTime, int iCurrentTime, int iStartX, int iStartY, int iEndX, int iEndY);
	int getPositionX();
	int getPositionY();

protected:
	/** Movement position calculator - give it start and end position and times
	and it works out current position for the current time.
	Notice also the MyMovementPosition class. */
	MovementPosition m_oMovement;

	// Pointer to the tile manager - we are going to use this!
	//TileManager* m_pTileManager;
};

