#ifndef _SCREEN_H
#define _SCREEN_H

#include "SceneManager.h"
#include "Scene.h"

#include "SpriteEntity.h"
#include "ShaderProgram.h"
#include "Vector3.h"
#include "EntityBase.h"

class Screen : public Scene
{
	// Screen States - MainMenu, Instructions, and Credits.
	enum SCREEN_STATE
	{
		MAIN_MENU = 0,
		INSTRUCTIONS,
		CREDITS,
		TOTAL
	};

	Screen(SceneManager* _sceneMgr); // This is used to register to SceneManager
	static Screen* sInstance; // The pointer to the object that gets registered

	float m_worldHeight;
	float m_worldWidth;
	
	SCREEN_STATE theScreenState;
	ShaderProgram* currProg;

	// Main Menu Background
	SpriteEntity* MainMenu_Background;
	// Instruction Background
	SpriteEntity* Instructions_Background;
	// Credit Background
	SpriteEntity* Credits_Background;

	// Start Game Button
	SpriteEntity* StartButton;
	// Instructions Button
	SpriteEntity* InstructionsButton;
	// Credits Button
	SpriteEntity* CreditButton;
	// Quit/Exit Game Button
	SpriteEntity* QuitButton;

	// Start Game Button Position
	Vector3 StartButtonPos;
	// Instructions Button Position
	Vector3 InstructionsButtonPos;
	// Credit Button Position
	Vector3 CreditsButtonPos;
	// Quit Button Position
	Vector3 QuitButtonPos;

	// Start Game Button Scale
	Vector3 StartButtonScale;
	// Instructions Button Scale
	Vector3 InstructionsButtonScale;
	// Credits Button Scale
	Vector3 CreditsButtonScale;
	// Quit/Exit Game Button Scale
	Vector3 QuitButtonScale;

	// Check if the mouse cursor is inside the buttons.
	bool isWithin;

	/*If the mouse is inside any buttons.
	The offset is so that whenever the cursor hover over any button 
	the button would be bigger to show a difference.*/
	Vector3 StartButtonScaleOffset;
	Vector3 InstructionsButtonScaleOffset;
	Vector3 CreditsButtonScaleOffset;
	Vector3 QuitButtonScaleOffset;

	/*This condition is to check if the mouse cursor is within the 
	buttons.*/
	float StartGameButtonCondition;
	float InstructionsButtonCondition;
	float CreditsButtonCondition;
	float QuitButtonCondition;

	// The mouse cursor position-related variables.
	Vector3 mousePos;
	float x_pos;
	float y_pos;

public:
	Screen();
	~Screen();

	void Init();
	void Update(double dt);
	void UpdateStartButton();
	void UpdateInstructionsButton();
	void UpdateCreditsButton();
	void UpdateQuitButton();
	void Render();
	void Exit();
};

#endif