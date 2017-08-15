#pragma once

#include "../PlayerInfo/PlayerInfo.h"

class CController
{
protected:
	CPlayerInfo* thePlayerInfo;

public:
	CController();
	virtual ~CController();

	// Create this controller
	virtual bool Create(CPlayerInfo* thePlayerInfo = NULL);
	// Read from the controller
	virtual int Read(const float deltaTime);

	// Detect and process front / back movement on the controller
	virtual bool Move_FrontBack(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	// Detect and process left / right movement on the controller
	virtual bool Move_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	// Detect and process zoom in / out on the controller
	virtual bool Zoom_InOut(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	// Detect and process look up / down on the controller
	virtual bool Look_UpDown(const float deltaTime, const bool direction, double cameraPitch);
	// Detect and process look left / right on the controller
	virtual bool Look_LeftRight(const float deltaTime, const bool direction, double cameraYaw);


};

