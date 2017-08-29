#ifndef _WIN_LOSE_SCREEN_H
#define _WIN_LOSE_SCREEN_H

#include "SceneManager.h"
#include "Scene.h"

#include "ShaderProgram.h"
#include "../SpriteEntity.h"
#include "../TextEntity.h"
#include <sstream>

class WinLoseScreen : public Scene
{
	// Enum states of Win/Lose Screen
	enum WIN_LOSE_STATE
	{
		//BASE = 0,
		WIN = 0,
		LOSE,
		TOTAL
	};

	WIN_LOSE_STATE theWinLoseState;

	WinLoseScreen(SceneManager* _sceneMgr); // This is used to register to SceneManager
	static WinLoseScreen* sInstance; // The pointer to the object that gets registered

	float m_worldHeight;
	float m_worldWidth;

	// The Level Name
	string Level;
	// Boolean to restart level
	bool m_bSwitchLevel;
	// Time before restart level
	float m_fTimeBeforeLevelChange;
	// Number for the states
	int States;

	ShaderProgram* currProg;

	// Win Screen Background
	SpriteEntity* Win_Background;
	// Lose Screen Background
	SpriteEntity* Lose_Background;

	// Text for the Timer
	TextEntity* textObj[1];

public:

	WinLoseScreen();
	~WinLoseScreen();

	// Set the Enum States
	void SetStates(int theWinLoseState);
	// Get the Enum States
	int GetStates();
	// Set the Level Name
	void SetLevel(string Level);
	// Get the Level Name
	string GetLevel();
	// Set the SwitchLevel Boolean
	void SetSwitchLevel(bool is_True);
	// Get the SwitchLevel Boolean
	bool GetSwitchLevel();

	static WinLoseScreen* GetInstance() { return sInstance; }

	void Init();
	void Update(double dt);
	void Render();
	void Exit();
};

#endif