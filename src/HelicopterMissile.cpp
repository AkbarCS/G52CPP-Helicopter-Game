#include "HelicopterMissile.h"
#include "JPGImage.h"
#include "HelicopterGameEngine.h"

bool HelicopterMissile::missileFired; 
int HelicopterMissile::objectHeight = 35;
int HelicopterMissile::objectWidth = 100;

HelicopterMissile::HelicopterMissile(HelicopterGameEngine* pEngine)
	: DisplayableObject(pEngine), myEngine(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 100;
	m_iCurrentScreenY = m_iPreviousScreenY = 125;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the object size as both height and width
	m_iDrawWidth = objectWidth;
	m_iDrawHeight = objectHeight;
	// And make it visible
	SetVisible(true);
}

HelicopterMissile::~HelicopterMissile()
{
}

void HelicopterMissile::Draw(void)
{
	if (!IsVisible())
		{
		return;
		}
	else
		{
		setMissileFired(true);
		// Draw an image loaded from a file.
		ImageData im;
		// Load the image file into an image object - at the normal size
		im.LoadImage("helicopter_missile.png");

		im.RenderImageWithMask(GetEngine()->GetForeground(),
			0, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			im.GetWidth(), im.GetHeight());

		// This will store the position at which the object was drawn
		// so that the background can be drawn over the top.
		// This will then remove the object from the screen.
		StoreLastScreenPositionForUndraw();
		}
}

// Allows a caller to specify where the object will move from and to and when
void HelicopterMissile::SetMovement(int iStartTime, int iEndTime, int iCurrentTime, int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMovement.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMovement.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();
}

// set movement
void HelicopterMissile::DoUpdate(int iCurrentTime)
{
	// Work out current position
	m_oMovement.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();

	// If movement has finished then request instructions
	if (m_oMovement.HasMovementFinished(iCurrentTime))
		{
		m_oMovement.Calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMovement.GetX();
		m_iCurrentScreenY = m_oMovement.GetY();
		}
	
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth())	
		{
			SetVisible(false);
			setMissileFired(false);
		} 

	myEngine->collisionDetectionMissile();

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

int HelicopterMissile::getPositionX()
{
	return m_iCurrentScreenX;
}

void HelicopterMissile::SetPositionX(int newPosition)
{
	m_iCurrentScreenX = newPosition;
}

int HelicopterMissile::getPositionY()
{
	return m_iCurrentScreenY;
}

void HelicopterMissile::SetPositionY(int newPosition)
{
	m_iCurrentScreenY = newPosition;
}

bool HelicopterMissile::getMissileFired()
{
	return missileFired;
}

void HelicopterMissile::setMissileFired(bool newBool)
{
	missileFired = newBool;
}

int HelicopterMissile::getHeight()
{
	return objectHeight;
}

int HelicopterMissile::getWidth()
{
	return objectWidth;
}

void HelicopterMissile::makeMissileVisible(bool value)
{
	this->SetVisible(value);
}