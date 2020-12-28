#include "header.h"
#include "templates.h"

#include "HelicopterGameEngine.h"
#include "Psyam12TileManager.h"
#include "HelicopterTiles.h"
#include "TileManager.h"
#include "HiScore.h"
#include "JPGImage.h"
#include "HelicopterSprite.h"
#include "HelicopterMissile.h"
#include "EnemyHelicopter.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
int HelicopterGameEngine::pauseStarted;
int updatedState, enableAI;

HelicopterGameEngine::HelicopterGameEngine()
	: BaseEngine(6), m_state(stateInit) 
{
}

HelicopterGameEngine::~HelicopterGameEngine()
{
}

HelicopterSprite* helicopter;
HelicopterMissile* missile;
EnemyHelicopter* enemyHelicopter;

int HelicopterGameEngine::InitialiseObjects(void)
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(4);

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.

	//set score counter to zero
	x = 0; 
	
	//set helicopterAdded to false
	helicopterAdded = 0; 

	updatedState = 0; 
	keyboardPushes = 0;
	enableAI = 0;

	helicopterX = 100;
	helicopterY = 125;

	return 0;
}

void HelicopterGameEngine::SetupBackgroundBuffer()
{
	switch(m_state)
		{
		case stateInit:
			{
			// Draw an image loaded from a file.
			ImageData im;
			// Load the image file into an image object - at the normal size
			im.LoadImage("helicopter_welcome_screen_image.jpg");
			im.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, im.GetWidth(), im.GetHeight());
	
			char* data[] = { "bbbbbbbbbbbbbbbb",
							 "bbbbbbbbbbbbbbbb",
							 "eeeeeeeeeeeeeeee",
							 "eeeeeeeeeeeeeeee",
							 "eeeeeeeeebeeeeee",
							 "eeeeeeeeebeeeeee",
							 "eeeeeeeeebeeeeee",
							 "eeeeeeeeeeeeeeee",
							 "eeeeeeeeeeeeeeee",
						   	 "eeeeeeeeeeeeeeee",
						 	 "bbbbbbbbbbbbbbbb",
							 "bbbbbbbbbbbbbbbb" };

			// Specify how many tiles wide and high
			gameTiles.SetSize(16, 12);
			// Set up the tiles
			for (int x = 0; x < 16; x++)
				for (int y = 0; y < 12; y++)
					gameTiles.SetValue(x, y, data[y][x] - 'a');

			// Specify the screen x,y of top left corner
			gameTiles.SetBaseTilesPositionOnScreen(0, 0);

			return;
			}
		case stateMain:
			{
			if (helicopterAdded == 0)
				{
				//adds the helicopter
				helicopter = new HelicopterSprite(this);
				enemyHelicopter = new EnemyHelicopter(this);

				StoreObjectInArray(0, helicopter);
				StoreObjectInArray(1, enemyHelicopter);
				StoreObjectInArray(2, NULL);
				StoreObjectInArray(3, NULL);
				helicopterAdded = 1;

				if (enableAI == 1)
					{
					helicopter->setAI(true);
					}
				
				enemyHelicopter->setHelicopterPresent(true);
				enemyHelicopter->SetMovement(GetTime(), GetTime() + 3000, GetTime(), 550, 120, 550, 470);
				}

			FillBackground(0xffffff);
			gameTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 15, 11);
			break;
			}
		case newMain:
			{
			if (updatedState == 0)
				{
				char* data[] = {"bbbbbbbbbbbbbbbb",
								"bbbbbbbbbbbbbbbb",
								"eeeeeeeeeeeeeeee",
								"eeeeeeeeeeeeeeee",
								"eeeeeeeeebeeeeee",
								"eeeeeeeeebeeeeee",
								"eeeeeeeeebeeeeee",
								"eeeeeeeeeeeeeeee",
								"eeeeeeeeeeeeeeee",
								"eeeeeeeeeeeeeeee",
								"bbbbbbbbbbbbbbbb",
								"bbbbbbbbbbbbbbbb" };

				//retrieve new background array
				data2 = HelicopterTiles::updateBackground(data);

				updatedState = 1;
				}
			else
				{
				data2 = HelicopterTiles::updateBackground(data2);
				}
			
			// Specify how many tiles wide and high
			gameTiles.SetSize(16, 12);
			// Set up the tiles
			for (int x = 0; x < 16; x++)
				{
				for (int y = 0; y < 12; y++)
					{
					gameTiles.SetValue(x, y, data2[y][x] - 'a');
					}
				}

			// Specify the screen x,y of top left corner
			gameTiles.SetBaseTilesPositionOnScreen(0, 0);

			FillBackground(0xffffff);
			gameTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 15, 11);

			break;
			}
		case stateHighScore:
			{
			FillBackground(0xffffff);
			break;
			}
		case statePaused:
			{
			FillBackground(0xffffff);
			gameTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 15, 11);
			break;
			}
		case stateEnd:
			{
			FillBackground(0xffffff);
			gameTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 15, 11);
			break;
			}
		}
}

/* Draw text labels */
void HelicopterGameEngine::DrawStrings()
{
	switch (m_state)
		{
		case stateInit:
			{
			DrawScreenString(250, 200, "Helicopter Game", 0xffffff, NULL);
			DrawScreenString(30, 220, "Avoid hitting the helicopter with other obstacles", 0xffffff, NULL);
			DrawScreenString(50, 240, "to survive. Use the up and down arrow keys to", 0xffffff, NULL);
			DrawScreenString(30, 260, "control the helicopter and x to launch a missile.", 0xffffff, NULL);
			DrawScreenString(220, 370, "Press Space to start", 0xffffff, NULL);
			DrawScreenString(190, 390, "Press 'a' to enable the AI", 0xffffff, NULL);
			DrawScreenString(90, 410, "Press Enter to view the high score table", 0xffffff, NULL);
			break;
			}
		case stateHighScore:
			{
			DrawScreenString(250, 50, "High Score Table", 0x000000, NULL);

			std::vector<int>* scores2 = HiScore::readScoresFromFile();

			for (int j2 = 0; j2 < scores2->size(); j2++)
				{
				printf("scores2 array %d\n", (*scores2)[j2]);
				}

			printf("read\n");

			int j;
			if (scores2->size() < 15)
				j = scores2->size();
			else
				j = 15;

			for (int i = 0; i < j; ++i)
				{
				std::string str1 = "Player " + std::to_string(i + 1);
				str1 += " Score = " + std::to_string((*scores2)[i]);

				DrawScreenString(190, 70 + (20 * i), str1.c_str(), 0x000000, NULL);
				}

			DrawScreenString(90, 500, "Press Enter to return back to the menu", 0x000000, NULL);

			break;
			}
		case statePaused:
			{
			DrawScreenString(270, 200, "Game is paused", 0x000000, NULL);
			break;
			}
		case stateEnd:
			{
			DrawScreenString(300, 240, "Game Over!", 0x000000, NULL);
			DrawScreenString(100, 260, "Press space to return to the main menu.", 0x000000, NULL);
			break;
			}
		}
}

/* Draw any string which should appear on top of moving objects - i.e. objects move behind these */
void HelicopterGameEngine::DrawStringsOnTop()
{
	int currentTime = GetTime();

	if (m_state == stateMain || m_state == newMain)
		{
		char buf1[128];
		x += 1;
		sprintf(buf1, "Score %d", x);
		DrawScreenString(30, 550, buf1, 0x00000, NULL);
		Redraw(true);
		}

	if ((m_state == stateMain || m_state == newMain) && (helicopter->returnAIState() == true) && currentTime >= newTime)
		{		
		m_state = newMain;
		SetupBackgroundBuffer();
		aiControl();
		//collisionDetection();
		newTime = newTime + 80;
		}
	else if ((m_state == stateMain || m_state == newMain) && currentTime >= newTime)
		{
		SetupBackgroundBuffer();	
		collisionDetection();
		newTime = newTime + 80;
		}
}

void HelicopterGameEngine::enemyHelicopterControl()
{
	m_state = newMain;
	keyboardPushes++;
		
	//add enemy helicopter after 20 key pushes
	if (keyboardPushes >= 20 && (enemyHelicopter->isHelicopterPresent() == false))
		{
		printf("adding enemy helicopter\n");
		enemyHelicopter = new EnemyHelicopter(this);
		StoreObjectInArray(1, enemyHelicopter);
		enemyHelicopter->SetMovement(GetTime(), GetTime() + 3000, GetTime(), 550, 120, 550, 470);
		enemyHelicopter->setHelicopterPresent(true);
		keyboardPushes = 0;
		}
}

/* Handle any key presses here.
   Note that the objects themselves (e.g. player) may also check whether a key is pressed */
void HelicopterGameEngine::KeyDown(int iKeyCode)
{
	if (m_state == stateMain || m_state == newMain)
		{
		enemyHelicopterControl();
		}

	switch (iKeyCode)
		{
		case SDLK_SPACE:		// SPACE starts the game if state = stateInit otherwise it pauses the game
			switch (m_state)
				{
				case stateInit:
					m_state = stateMain;
					pauseStarted = 0;
					newTime = GetTime();
					SetupBackgroundBuffer();
					Redraw(true);
					break;
				case stateMain:
					m_state = statePaused;
					enemyHelicopter->makeHelicopterVisible(false);
					pauseStarted = 1;
					m_iPauseStarted = GetTime();
					SetupBackgroundBuffer();
					Redraw(true);
					break;
				case newMain:
					m_state = statePaused;
					enemyHelicopter->makeHelicopterVisible(false);
					pauseStarted = 1;
					m_iPauseStarted = GetTime();
					SetupBackgroundBuffer();
					Redraw(true);
					break;
				case statePaused:
					m_state = stateMain;
					enemyHelicopter->makeHelicopterVisible(true);
					pauseStarted = 0;
					IncreaseTimeOffset(m_iPauseStarted - GetTime());
					SetupBackgroundBuffer();
					Redraw(true);
					break;
				case stateEnd:
					m_state = stateInit;
					pauseStarted = 1;
					enableAI = 0;
					enemyHelicopter->makeHelicopterVisible(false);
					helicopter->setAI(false);
					HiScore::writeScoreToFile(x);
					InitialiseObjects();
					SetupBackgroundBuffer();
					Redraw(true);
					break;
				}
			break;
		case SDLK_RETURN:		//view high score table
			switch (m_state)
				{
				case stateInit:
					m_state = stateHighScore;
					SetupBackgroundBuffer();
					Redraw(true);
					break;
				case stateHighScore:
					m_state = stateInit;
					SetupBackgroundBuffer();
					Redraw(true);
					break;
				}
			break;
		case SDLK_a:			//'a' enables the AI
			switch (m_state)
				{
				case stateInit:
					{
					m_state = stateMain;					
					enableAI = 1;
					SetupBackgroundBuffer();
					break;
					}
				}
			break;
		case SDLK_x:			//'x' launches the missile which can be used to destroy obstacles
			{
			if (m_state == stateMain || m_state == newMain)
				{
				if (missile->getMissileFired() == false)
					{
					int helicopterX = helicopter->getPositionX();
					int helicopterY = helicopter->getPositionY();

					missile = new HelicopterMissile(this);

					StoreObjectInArray(2, missile);

					missile->setMissileFired(true);
					missile->SetMovement(GetTime(), GetTime() + 1000, GetTime(), helicopter->getPositionX(), helicopter->getPositionY(), GetScreenWidth(), helicopter->getPositionY());
					break;
					}
				}
			}
		}
}

//Clicking the left mouse button causes the helicopter to rise up
void HelicopterGameEngine::MouseDown(int iButton, int iX, int iY)
{
	if (m_state == stateMain || m_state == newMain)
		{
		if (iButton == 1)
			{
			printf("mouse left\n");
			enemyHelicopterControl();
			helicopter->changeDirection(0);
			SetupBackgroundBuffer();
			Redraw(true);
			}
		else if (iButton == 3)
			{
			printf("mouse right\n");
			enemyHelicopterControl();
			helicopter->changeDirection(1);
			SetupBackgroundBuffer();
			Redraw(true);
			}
		}
}

void HelicopterGameEngine::collisionDetection()
{	
	int helicopterWidth = HelicopterSprite::getWidth();
	int helicopterHeight = HelicopterSprite::getHeight();	

	int helicopterLeft = helicopter->getPositionX();
	int helicopterRight = (helicopter->getPositionX())+helicopterWidth;
	int helicopterTop = helicopter->getPositionY();
	int helicopterBottom = (helicopter->getPositionY())+helicopterHeight;	
	int helicopterCenterX = (helicopter->getPositionX()) + (helicopterWidth/2);
			
	int tileX1 = helicopterRight / 50;
	int tileX2 = helicopterLeft / 50;
	int tileY1 = helicopterTop / 50;
	int tileY2 = helicopterBottom / 50;
	int tileX3 = helicopterCenterX / 50;

	if (m_state == stateMain)
		{
		char* datatmp[] = {"bbbbbbbbbbbbbbbb",
						   "bbbbbbbbbbbbbbbb",
						   "eeeeeeeeeeeeeeee",
						   "eeeeeeeeeeeeeeee",
						   "eeeeeeeeebeeeeee",
						   "eeeeeeeeebeeeeee",
						   "eeeeeeeeebeeeeee",
						   "eeeeeeeeeeeeeeee",
						   "eeeeeeeeeeeeeeee",
						   "eeeeeeeeeeeeeeee",
						   "bbbbbbbbbbbbbbbb",
						   "bbbbbbbbbbbbbbbb" };

		if (datatmp[tileY1][tileX1] == 'b' || datatmp[tileY1][tileX2] == 'b' || datatmp[tileY2][tileX1] == 'b' || datatmp[tileY2][tileX2] == 'b' || datatmp[tileY1][tileX3] == 'b' || datatmp[tileY2][tileX3] == 'b')
			{
			m_state = stateEnd;
			pauseStarted = 1;
			}
		}
	else if (m_state == newMain)
		{
		if (data2[tileY1][tileX1] == 'b' || data2[tileY1][tileX2] == 'b' || data2[tileY2][tileX1] == 'b' || data2[tileY2][tileX2] == 'b' || data2[tileY1][tileX3] == 'b' || data2[tileY2][tileX3] == 'b')
			{
			m_state = stateEnd;
			pauseStarted = 1;
			}
		} 
}

void HelicopterGameEngine::collisionDetectionMissile()
{
	int missileWidth = HelicopterMissile::getWidth();
	int missileHeight = HelicopterMissile::getHeight();
	
	int missileX = missile->getPositionX();
	int missileY = missile->getPositionY();

	int missileRight = (missile->getPositionX()) + missileWidth;
	int missileTop = missile->getPositionY();
	int missileBottom = (missile->getPositionY()) + missileHeight;

	int missileTileRight = missileRight / 50;
	int missileTileTop = missileTop / 50;
	int missileTileBottom = missileBottom / 50;

	int redrawBackground = 0;
	int deleteTileX;
	int deleteTileY;

	int destroyed = 0;

	//delete the enemy helicopter
	if (enemyHelicopter->isHelicopterPresent() == true && missile->getMissileFired() == true)
		{ 
		int enemyHelicopterWidth = EnemyHelicopter::getWidth();
		int enemyHelicopterHeight = EnemyHelicopter::getHeight();

		int enemyHelicopterX = enemyHelicopter->getPositionX();
		int enemyHelicopterY = enemyHelicopter->getPositionY();
		
		int enemyLeft = enemyHelicopterX;
		int enemyTop = enemyHelicopterY;
		int enemyBottom = enemyHelicopterY + enemyHelicopterHeight;

		if (enemyLeft - missileRight <= 0)
			{ 
			for (int i = missileTop; i < missileBottom; i++)
				{
				for (int j = enemyTop; j < enemyBottom; j++)
					{
					if (i == j)
						{
						enemyHelicopter->SetVisible(false);
						enemyHelicopter->setHelicopterPresent(false);
						missile->makeMissileVisible(false);
						missile->setMissileFired(false);
						}
					}
				}
			}
		}

	//delete walls
	if (m_state == stateMain && destroyed == 0)
		{
		char* datatmp[] = { "bbbbbbbbbbbbbbbb",
							"bbbbbbbbbbbbbbbb",
							"eeeeeeeeeeeeeeee",
							"eeeeeeeeeeeeeeee",
							"eeeeeeeeebeeeeee",
							"eeeeeeeeebeeeeee",
							"eeeeeeeeebeeeeee",
							"eeeeeeeeeeeeeeee",
							"eeeeeeeeeeeeeeee",
							"eeeeeeeeeeeeeeee",
							"bbbbbbbbbbbbbbbb",
							"bbbbbbbbbbbbbbbb" };

		if (datatmp[missileTileTop][missileTileRight] == 'b') 
			{
			redrawBackground = 1;
			deleteTileX = missileTileRight;
			deleteTileY = missileTileTop;
			}
		else if (datatmp[missileTileBottom][missileTileRight] == 'b')
			{
			redrawBackground = 1;
			deleteTileX = missileTileRight;
			deleteTileY = missileTileTop;
			}
		}
	else if (m_state == newMain && destroyed == 0)
		{
		if (data2[missileTileTop][missileTileRight] == 'b')
			{
			redrawBackground = 1;
			deleteTileX = missileTileRight;
			deleteTileY = missileTileTop;
			}
		else if (data2[missileTileBottom][missileTileRight] == 'b')
			{
			redrawBackground = 1;
			deleteTileX = missileTileRight;
			deleteTileY = missileTileTop;
			}
		}

	if (redrawBackground == 1)
		{
		data2[deleteTileY][deleteTileX] = 'e';
		data2[deleteTileY-1][deleteTileX] = 'e';
		data2[deleteTileY+1][deleteTileX] = 'e';

		missile->makeMissileVisible(false);
		missile->setMissileFired(false);

		SetupBackgroundBuffer();
		}
}

int HelicopterGameEngine::getPauseState()
{
	return pauseStarted;
}

void HelicopterGameEngine::aiControl()
{
	//a depth first search algorithm is used to find the route between the obstacles
	int positions[6];
	int count = 0;
	int change[3];
	int nodesToExpand[1000];

	change[0] = 0;
	change[1] = -50;
	change[2] = 50;

	for (int i2 = 0; i2 < 6; i2++)
		{
		positions[i2] = 0;
		}

	for (int j = 0; j < 1000; j++)
		{
		nodesToExpand[j] = 0;
		}

	for (int i = 0; i < 3; i++)
		{
		nodesToExpand[i] = helicopterY + change[i];
		}

	int positionXtmp = helicopterX;
	int positionYtmp = helicopterY;
	bool tmpBool;

	positionXtmp += 50;

	while(positionXtmp <= 400)
		{
		if (nodesToExpand[0] >= 120 && nodesToExpand[0] <= 480)
			{ 
			if (m_state == stateMain)
				{
					char* data[] = { "bbbbbbbbbbbbbbbb", 
									 "bbbbbbbbbbbbbbbb",
									 "eeeeeeeeeeeeeeee",
									 "eeeeeeeeeeeeeeee",
									 "eeeeeeeeebeeeeee",
									 "eeeeeeeeebeeeeee",
									 "eeeeeeeeebeeeeee",
									 "eeeeeeeeeeeeeeee",
									 "eeeeeeeeeeeeeeee",
									 "eeeeeeeeeeeeeeee",
									 "bbbbbbbbbbbbbbbb",
									 "bbbbbbbbbbbbbbbb" };

				tmpBool = AIcollisionDetection(data, positionXtmp, positionYtmp);
				}
			else
				{
				tmpBool = AIcollisionDetection(data2, positionXtmp, positionYtmp);
				}

			if (tmpBool == true)
				{
				//try new node relative to the parent node, i.e. same x co-ordinate and different y co-ordinate
				//delete first element and shift elements to the left
				nodesToExpand[0] = 0;

				printf("starting\n");

				//shift elements to the left
				while (nodesToExpand[0] == 0)
				{
					bool containsAllZeroes = true;

					for (int i1 = 0; i1 < 999; i1++)
					{
						if (nodesToExpand[i1] != 0)
						{
							containsAllZeroes = false;
						}

						if (nodesToExpand[i1] != 0 && (nodesToExpand[i1] <= 120 || nodesToExpand[i1] >= 480))
						{
							nodesToExpand[i1] = 0;
						}
						else
						{
							nodesToExpand[i1] = nodesToExpand[i1 + 1];
						}						
					}

					if (containsAllZeroes == true)
					{
						break;
					}
				}

				printf("done\n");
			
				if (nodesToExpand[0] == 0)
				{	
					int lastIndexFilled = 0;
					for (int i = 0; i < 3; i++)
					{
						if (positionYtmp + change[i] >= 120 && positionYtmp + change[i] <= 480 && positionYtmp != positionYtmp + change[i])
						{
							nodesToExpand[lastIndexFilled] = positionYtmp + change[i];
							lastIndexFilled++;
						}						
					}
				}
				else if (nodesToExpand[0] <= 120)
				{
					nodesToExpand[0] += 50;
				}
				else if (nodesToExpand[0] >= 480)
				{
					nodesToExpand[0] -= 50;
				}

				positionYtmp = nodesToExpand[0];	
				printf("%d\n", positionYtmp);

				//printf("value of nodes to expand is %d\n", nodesToExpand[0]);
				}
			else if (tmpBool == false)
				{
				//different x co-ordinate				
				positionXtmp += 50;

				int tmp[1000];

				//shift elements to the 3 places to the right
				for (int i2 = 0; i2 < 996; i2++)
					{
					tmp[i2+3] = nodesToExpand[i2];
					}

				for (int i3 = 0; i3 < 996; i3++)
					{
					nodesToExpand[i3] = tmp[i3+3];
					}
				
				//add new y co-ordinates to beginning of nodesToExpand array
				for (int i = 0; i < 3; i++)
					{
					nodesToExpand[i] = positionYtmp + change[i];
					}

				positions[count] = positionYtmp;
				count++;
				}
			}
		}	

	for (int j = 0; j < 6; j++)
		{
		int helicopterYprevious = positionYtmp;
		helicopterY = positions[j];
		printf("update %d\n", helicopterY);
		helicopter->SetMovement(GetTime(), GetTime() + 30, GetTime(), helicopterX, helicopterYprevious, helicopterX, positions[j]);
		}
}

bool HelicopterGameEngine::AIcollisionDetection(char** data, int positionX, int positionY)
{
	int helicopterWidth = HelicopterSprite::getWidth();
	int helicopterHeight = HelicopterSprite::getHeight();

	int helicopterLeft = positionX;
	int helicopterRight = positionX + helicopterWidth;
	int helicopterTop = positionY;
	int helicopterBottom = positionY + helicopterHeight;
	int helicopterCenterX = positionX + (helicopterWidth / 2);

	int tileX1 = helicopterRight / 50;
	int tileX2 = helicopterLeft / 50;
	int tileY1 = helicopterTop / 50;
	int tileY2 = helicopterBottom / 50;
	int tileX3 = helicopterCenterX / 50;

	if (tileX1 > 15 || tileX2 > 15 || tileX3 > 15 || tileY1 > 11 || tileY2 > 11)
		{
		return false;
		}

	if (m_state == stateMain || m_state == newMain)
		{
		if (data[tileY1][tileX1] == 'b' || data[tileY1][tileX2] == 'b' || data[tileY2][tileX1] == 'b' || data[tileY2][tileX2] == 'b' || data[tileY1][tileX3] == 'b' || data[tileY2][tileX3] == 'b')
			{
			return true;
			}
		}
	
	return false;
}	