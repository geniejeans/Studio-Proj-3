#include "Keyboard.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

#include "KeyboardController.h"
#include "../PlayerInfo/PlayerInfo.h"

CKeyboard::CKeyboard()
{
}


CKeyboard::~CKeyboard()
{
}

// Create this controller
bool CKeyboard::Create(CPlayerInfo* thePlayerInfo)
{
	CController::Create(thePlayerInfo);
	return false;
}


// Read from the controller
int CKeyboard::Read(const float deltaTime)
{
	CController::Read(deltaTime);
	
	// Process the keys for customisation
	if (KeyboardController::GetInstance()->IsKeyDown('W')) //W
		Move_FrontBack(deltaTime, true,5.f);
	if (KeyboardController::GetInstance()->IsKeyDown('S')) //S
		Move_FrontBack(deltaTime, false,5.f);
	if (KeyboardController::GetInstance()->IsKeyDown('A')) //A
		Move_LeftRight(deltaTime, true, 5.f);
	if (KeyboardController::GetInstance()->IsKeyDown('D')) //D
		Move_LeftRight(deltaTime, false, 5.f);
	//if (KeyboardController::GetInstance()->IsKeyDown('N')) //D
	//	Zoom_InOut(deltaTime, true, 5.f);
	//if (KeyboardController::GetInstance()->IsKeyDown('M')) //D
	//	Zoom_InOut(deltaTime, false, 5.f);
	if (KeyboardController::GetInstance()->IsKeyDown(VK_LEFT))
		Look_LeftRight(deltaTime, true, 1);
	if (KeyboardController::GetInstance()->IsKeyDown(VK_RIGHT))
		Look_LeftRight(deltaTime, false, 1);
	if (KeyboardController::GetInstance()->IsKeyDown(VK_UP))
		Look_UpDown(deltaTime, true, 1);
	if (KeyboardController::GetInstance()->IsKeyDown(VK_DOWN))
		Look_UpDown(deltaTime, false, 1);

	return 0;
}