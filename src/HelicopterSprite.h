#pragma once

#include "DisplayableObject.h"
#include "MovementPosition.h"
#include "HelicopterGameEngine.h"

class HelicopterSprite :
	public DisplayableObject
{
public:
	HelicopterSprite(HelicopterGameEngine* pEngine);
	~HelicopterSprite();
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	void changeDirection(int upOrDown);
	void SetMovement(int iStartTime, int iEndTime, int iCurrentTime, int iStartX, int iStartY, int iEndX, int iEndY);
	void setAI(bool newAIstate);
	bool returnAIState();
	int getPositionX();
	void SetPositionX(int newPosition);
	int getPositionY();
	void SetPositionY(int newPosition);
	static int getHeight();
	static int getWidth();

protected:
	/** Movement position calculator - give it start and end position and times
	and it works out current position for the current time.
	Notice also the MyMovementPosition class. */
	MovementPosition m_oMovement;

private:
	HelicopterGameEngine* myEngine;
	static int objectHeight;
	static int objectWidth;
	bool aiState;
};

