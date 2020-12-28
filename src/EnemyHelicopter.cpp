#include "EnemyHelicopter.h"
#include "JPGImage.h"
#include "HelicopterGameEngine.h"

bool EnemyHelicopter::helicopterPresent;
int EnemyHelicopter::objectHeight = 35;
int EnemyHelicopter::objectWidth = 100;

EnemyHelicopter::EnemyHelicopter(HelicopterGameEngine* pEngine)
	: DisplayableObject(pEngine), myEngine(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 400;
	m_iCurrentScreenY = m_iPreviousScreenY = 500;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the object size as both height and width
	m_iDrawWidth = objectWidth;
	m_iDrawHeight = objectHeight;
	// And make it visible
	SetVisible(true);
}

EnemyHelicopter::~EnemyHelicopter()
{
}

void EnemyHelicopter::Draw(void)
{
	if (!IsVisible())
	{
		return;
	}
	else
	{
		setHelicopterPresent(true);
		// Draw an image loaded from a file.
		ImageData im;
		// Load the image file into an image object - at the normal size
		im.LoadImage("enemy_helicopter_sprite.png");

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
void EnemyHelicopter::SetMovement(int iStartTime, int iEndTime, int iCurrentTime, int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMovement.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMovement.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();
}

// set movement
void EnemyHelicopter::DoUpdate(int iCurrentTime)
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

	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth())
	{
		SetVisible(false);
		setHelicopterPresent(false);
	}

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

int EnemyHelicopter::getPositionX()
{
	return m_iCurrentScreenX;
}

void EnemyHelicopter::SetPositionX(int newPosition)
{
	m_iCurrentScreenX = newPosition;
}

int EnemyHelicopter::getPositionY()
{
	return m_iCurrentScreenY;
}

void EnemyHelicopter::SetPositionY(int newPosition)
{
	m_iCurrentScreenY = newPosition;
}

bool EnemyHelicopter::isHelicopterPresent()
{
	return helicopterPresent;
}

void EnemyHelicopter::setHelicopterPresent(bool newBool)
{
	helicopterPresent = newBool;
}

int EnemyHelicopter::getHeight()
{
	return objectHeight;
}

int EnemyHelicopter::getWidth()
{
	return objectWidth;
}

void EnemyHelicopter::makeHelicopterVisible(bool value)
{
	this->SetVisible(value);
}