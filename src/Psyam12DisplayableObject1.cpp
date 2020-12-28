#include "Psyam12DisplayableObject1.h"

#include "header.h"
#include "templates.h"

Psyam12DisplayableObject1::Psyam12DisplayableObject1(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 100;
	m_iCurrentScreenY = m_iPreviousScreenY = 100;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the object size as both height and width
	m_iDrawWidth = 100;
	m_iDrawHeight = 50;
	// And make it visible
	SetVisible(true);
}


Psyam12DisplayableObject1::~Psyam12DisplayableObject1()
{
}

void Psyam12DisplayableObject1::Draw(void)
{
	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x00ff00);
	
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();

}

// Allows a caller to specify where the object will move from and to and when
void Psyam12DisplayableObject1::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
	int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMovement.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMovement.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();
}


// set movement
void Psyam12DisplayableObject1::DoUpdate(int iCurrentTime)
{
	// Work out current position
	m_oMovement.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();

	// If movement has finished then request instructions
	if (m_oMovement.HasMovementFinished(iCurrentTime))
	{
		m_oMovement.Reverse();
		m_oMovement.Calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMovement.GetX();
		m_iCurrentScreenY = m_oMovement.GetY();
	}

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

int Psyam12DisplayableObject1::getPositionX()
{
	return m_iCurrentScreenX;
}

int Psyam12DisplayableObject1::getPositionY()
{
	return m_iCurrentScreenY;
}