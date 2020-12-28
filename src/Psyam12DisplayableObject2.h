#pragma once
#include "DisplayableObject.h"
#include "Psyam12Engine.h"

class Psyam12DisplayableObject2 :
	public DisplayableObject	
{
public:
	Psyam12DisplayableObject2(BaseEngine* pEngine);
	~Psyam12DisplayableObject2();
	void Draw(void);
	void DoUpdate(int iCurrentTime);
	void UnDrawStrings(int x, int y);
	int getPositionX();
	int getPositionY();
};

