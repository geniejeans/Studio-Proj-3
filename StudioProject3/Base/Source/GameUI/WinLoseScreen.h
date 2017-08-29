#ifndef _WIN_LOSE_SCREEN_H
#define _WIN_LOSE_SCREEN_H

#include "SceneManager.h"
#include "Scene.h"

#include "ShaderProgram.h"
#include "../SpriteEntity.h"

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

	WinLoseScreen(SceneManager* _sceneMgr); // This is used to register to SceneManager
	static WinLoseScreen* sInstance; // The pointer to the object that gets registered

	float m_worldHeight;
	float m_worldWidth;

	WIN_LOSE_STATE theWinLoseState;
	ShaderProgram* currProg;

	// Win Screen Background
	SpriteEntity* Win_Background;
	// Lose Screen Background
	SpriteEntity* Lose_Background;

public:
	WinLoseScreen();
	~WinLoseScreen();

	// Set the Enum States
	void SetStates();
	// Get the Enum States
	int GetStates();

	void Init();
	void Update(double dt);
	void Render();
	void Exit();
};

#endif