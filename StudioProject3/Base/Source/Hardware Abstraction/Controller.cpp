#include "Controller.h"
#include <iostream>
using namespace std;

CController::CController()
	: thePlayerInfo(NULL)
{
}


CController::~CController()
{
	// We just set thePlayerInfo to NULL without deleting. SceneText will delete this.
	if (thePlayerInfo)
		thePlayerInfo = NULL;
}


// Create this controller
bool CController::Create(CPlayerInfo* thePlayerInfo)
{
	this->thePlayerInfo = thePlayerInfo;
	return false;
}

// Read from the controller
int CController::Read(const const float deltaTime)
{
	return 0;
}

// Detect and process front / back movement on the controller
bool CController::Move_FrontBack(const float deltaTime, const bool direction, const float speedMultiplier)
{
	if (thePlayerInfo)
	{
		thePlayerInfo->Move_FrontBack(deltaTime, direction, speedMultiplier);
	}
	return false;
}

// Detect and process left / right movement on the controller
bool CController::Move_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier)
{
	if (thePlayerInfo)
	{
		thePlayerInfo->Move_LeftRight(deltaTime, direction, speedMultiplier);
	}
	return false;
}


// Detect and process zoom in / out on the controller
bool CController::Zoom_InOut(const float deltaTime, const bool direction, const float speedMultiplier)
{
	if (thePlayerInfo)
	{
		thePlayerInfo->Zoom_InOut(deltaTime, direction, speedMultiplier);
	}
	return false;
}

// Detect and process look up / down on the controller
bool CController::Look_UpDown(const float deltaTime, const bool direction, double cameraPitch)
{
	if (thePlayerInfo)
	{
		thePlayerInfo->Look_UpDown(deltaTime, direction, cameraPitch);
	}
	return false;
}

// Detect and process look left / right on the controller
bool CController::Look_LeftRight(const float deltaTime, const bool direction, double cameraYaw)
{
	if (thePlayerInfo)
	{
		thePlayerInfo->Look_LeftRight(deltaTime, direction, cameraYaw);
	}
	return false;
}
