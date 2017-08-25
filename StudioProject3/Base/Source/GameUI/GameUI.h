#pragma once
#include "SingletonTemplate.h"

class GroundEntity;

class GameUI : public Singleton<GameUI>
{
private:


public:
	void Update(GroundEntity *groundEntity);
	GameUI() {};
	~GameUI() {};

	static bool m_bIsRendered;

	bool GetBombRender();
	static void SetBombRender(bool IsRendered);
};