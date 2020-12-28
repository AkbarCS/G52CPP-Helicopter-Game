#include "header.h"
#include "templates.h"

#include "Psyam12Engine.h"
#include "HelicopterTiles.h"

#include "Psyam12DisplayableObject1.h"
#include "Psyam12DisplayableObject2.h"
#include "Psyam12DisplayableObject3.h"

Psyam12Engine::Psyam12Engine()
	: BaseEngine(6)
{
}

Psyam12Engine::~Psyam12Engine()
{
}

Psyam12DisplayableObject1* object1;
Psyam12DisplayableObject2* object2;

int Psyam12Engine::InitialiseObjects(void)
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();
	
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(3);
	
	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	
	//adds a rectangle
	object1 = new Psyam12DisplayableObject1(this);

	//adds an oval
	object2 = new Psyam12DisplayableObject2(this);

	// object 1 has a movement object, tells it to move from
	// position a to position b, over a specific period of time.
	// The update for the ball will reverse the move at the end of this time
	object1->SetMovement(GetTime(), GetTime() + 1000, GetTime(), 100, 100, 300, 400);
	
	StoreObjectInArray(0, object1);
	StoreObjectInArray(1, object2);
	StoreObjectInArray(2, NULL); 

	x = 0;

	return 0;
}

void Psyam12Engine::SetupBackgroundBuffer()
{
	FillBackground(0xffffff);

	DrawBackgroundShortenedArrow(10, 40, 300, 300, 3, 3, 0xFFA500, 30, 30);

	//obTileManager.DrawAllTilesAt2(this, this->GetBackground(), 0, 0, 4, 4, 200, 300, 0x404000);
}

/* Draw text labels */
void Psyam12Engine::DrawStrings()
{
	CopyBackgroundPixels(50/*X*/, 50/*Y*/, GetScreenWidth(), 30/*Height*/);
	DrawScreenString(400, 400, "Score", 0xFFA500, NULL);

	UnDrawStrings(0, 0);
} 

/* Redraw the background over where you are drawing the strings.*/
void Psyam12Engine::UnDrawStrings(int x, int y)
{
	CopyBackgroundPixels( x, y, GetScreenWidth(), 100/*Height*/ );
}

/* Draw any string which should appear on top of moving objects - i.e. objects move behind these */
void Psyam12Engine::DrawStringsOnTop()
{
	// Build the string to print
	char buf1[128];
	x += 1;
	sprintf(buf1, "Counter %d", x, x);
	DrawScreenString(0, 0, buf1, 0xff00ff, NULL);

	object1X = object1->getPositionX();
	object1Y = object1->getPositionY();

	object2X = object2->getPositionX();
	object2Y = object2->getPositionY();
	
	char buf2[128];
	char buf3[128];

	//check if there is a collision between a circle and rectangle
	if (collisionDetection(25, 25) == 1)
		{
		sprintf(buf2, "Collison");
		sprintf(buf3, "Collison");
		}
	else 
		{
		sprintf(buf2, "Green rectangle %f %f", object1X, object1Y);
		sprintf(buf3, "Blue circle %f %f", object2X, object2Y);
		}

	DrawScreenString(10, 30, buf2, 0xff00ff, NULL);
	DrawScreenString(10, 50, buf3, 0xff00ff, NULL);
}

//collision detection - this works for collisions between two objects. The position of the center is obtained.
//From there, using pythagoras's theorem, the distance between the two object centers are calculated. The final
//result is the pythagorean distance minus the distances from the center to the edge of both objects.
int Psyam12Engine::collisionDetection(int shape1Radius, int shape2Radius)
{
	double xSquared = pow(abs(object2X - object1X), 2);
	double ySquared = pow(abs(object2Y - object1Y), 2);

	if ((sqrt(xSquared + ySquared) - (shape1Radius+shape2Radius)) <= 0)
		{
		return 1;
		}
	else 
		{
		return 0;
		}
}