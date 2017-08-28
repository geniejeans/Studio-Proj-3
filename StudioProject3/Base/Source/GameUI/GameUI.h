#pragma once
#include "SingletonTemplate.h"

class GroundEntity;

class GameUI : public Singleton<GameUI>
{
private:
	// Boolean for Shield
	static bool m_bShieldIsPressed;

public:
	void Update(GroundEntity *groundEntity);
	GameUI() {};
	~GameUI() {};

	static bool m_bIsRendered;

	bool GetBombRender();
	static void SetBombRender(bool IsRendered);
	// Set the Boolean for Shield.
	static void SetShieldIsPressed(bool is_True);
	// Get the Boolean for Shield.
	bool GetShieldIsPressed();
};