#pragma once
#include "BaseEngine.h"
#include "TileManager.h"
#include "HelicopterTiles.h"

class TileManager;

class HelicopterGameEngine :
	public BaseEngine
{
public:
	HelicopterGameEngine();
	~HelicopterGameEngine();
	int InitialiseObjects(void);
	void SetupBackgroundBuffer();
	void DrawStrings();
	void DrawStringsOnTop();
	void enemyHelicopterControl();
	void KeyDown(int iKeyCode);
	void MouseDown(int iButton, int iX, int iY);
	void collisionDetection();
	void collisionDetectionMissile();
	static int getPauseState();
	void aiControl();
	bool AIcollisionDetection(char** data, int positionX, int positionY);

	// State number
	enum State { stateInit, stateMain, newMain, statePaused, stateHighScore, stateEnd };
	State m_state;	
	int m_iPauseStarted;
	

private:		
	int x;
	int keyboardPushes;
	int newTime;
	HelicopterTiles gameTiles;
	int helicopterAdded;
	static int pauseStarted;
	char** data2;
	int helicopterX;
	int helicopterY;
	
};
