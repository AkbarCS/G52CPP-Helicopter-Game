#pragma once

#include "DisplayableObject.h"
#include "MovementPosition.h"
#include "HelicopterGameEngine.h"

class HelicopterMissile :
	public DisplayableObject
{
public:
	HelicopterMissile(HelicopterGameEngine* pEngine);
	~HelicopterMissile();
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	void SetMovement(int iStartTime, int iEndTime, int iCurrentTime, int iStartX, int iStartY, int iEndX, int iEndY);
	int getPositionX();
	void SetPositionX(int newPosition);
	int getPositionY();
	void SetPositionY(int newPosition);
	void SetPositionUp(double dX, double dY);
	void SetPositionDown(double dX, double dY);
	static bool getMissileFired();
	static void setMissileFired(bool newBool);
	static int getHeight();
	static int getWidth();
	void makeMissileVisible(bool value);

protected:
	/** Movement position calculator - give it start and end position and times
	and it works out current position for the current time.
	Notice also the MyMovementPosition class. */
	MovementPosition m_oMovement;
	static bool missileFired;

private:
	HelicopterGameEngine* myEngine;
	static int objectHeight;
	static int objectWidth;
};

