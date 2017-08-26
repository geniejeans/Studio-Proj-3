// Player's Troops Shield.
#ifndef _SHIELD_H
#define _SHIELD_H

#include "SingletonTemplate.h"

#include "../GameUI/GameUI.h"
#include <iostream>

using std::cout;
using std::endl;

class Shield : public Singleton<Shield>
{
	// Boolean for Shield Activation
	bool m_bShieldActive;
	double elapsedTime;
	// Boolean for Rendering the appropriate texture
	bool m_bRenderTexture;

public:
	Shield();
	~Shield();

	void Update(double dt);

	// Set the Boolean for Shield Activation
	void SetShieldActive();
	// Get the Boolean for Shield Activation
	bool GetShieldActive();
};

#endif