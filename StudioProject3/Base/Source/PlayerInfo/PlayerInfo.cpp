#include "PlayerInfo.h"
#include <iostream>
#include "MouseController.h"
#include "KeyboardController.h"
#include "Mtx44.h"
#include "../Projectile/Projectile.h"

// Allocating and initializing CPlayerInfo's static data member.  
// The pointer is allocated but not the object's constructor.
CPlayerInfo *CPlayerInfo::s_instance = 0;

CPlayerInfo::CPlayerInfo(void)
	: m_dSpeed(40.0)
	, m_dElapsedTime(0.0)
	, attachedCamera(NULL)
	, m_pTerrain(NULL)
	, b_collision(false)
	, elapsedTime_timer(10.0)

{
}

CPlayerInfo::~CPlayerInfo(void)
{
	m_pTerrain = NULL;
}

// Initialise this class instance
void CPlayerInfo::Init(void)
{
	// Set the default values
	defaultPosition.Set(0, 420, 740);
	defaultTarget.Set(0, 100, 250);
	defaultUp.Set(0,1,0);

	// Set the current values
	position.Set(0, 420, 740);
	target.Set(0, 100, 250);
	up.Set(0, 1, 0);

	// Set Boundary
	maxBoundary.Set(1,1,1);
	minBoundary.Set(-1, -1, -1);

	elapsedTime_timer = 10.0f;

}

// Set the time countdown
void CPlayerInfo::SetTimeCountdown(const double elapsedTime_timer)
{
	this->elapsedTime_timer = elapsedTime_timer;
}


// Set position
void CPlayerInfo::SetPos(const Vector3& pos)
{
	position = pos;
}

// Set target
void CPlayerInfo::SetTarget(const Vector3& target)
{
	this->target = target;
}

// Set position
void CPlayerInfo::SetUp(const Vector3& up)
{
	this->up = up;
}

// Set the boundary for the player info
void CPlayerInfo::SetBoundary(Vector3 max, Vector3 min)
{
	maxBoundary = max;
	minBoundary = min;
}

// Set the terrain for the player info
void CPlayerInfo::SetTerrain(GroundEntity* m_pTerrain)
{
	if (m_pTerrain != NULL)
	{
		this->m_pTerrain = m_pTerrain;

		SetBoundary(this->m_pTerrain->GetMaxBoundary(), this->m_pTerrain->GetMinBoundary());
		maxBoundary.y = 420.f;
		minBoundary.y = 150.f;
	}
}

void CPlayerInfo::SetCollision(bool collide)
{
	b_collision = collide;
}

// Reset this player instance to default
void CPlayerInfo::Reset(void)
{
	// Set the current values to default values
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

// Get position x of the player(I've changed it to int)
Vector3 CPlayerInfo::GetPos(void) const
{
	return position;
}

// Get target
Vector3 CPlayerInfo::GetTarget(void) const
{
	return target;
}
// Get Up
Vector3 CPlayerInfo::GetUp(void) const
{
	return up;
}
/********************************************************************************
 Hero Update
 ********************************************************************************/
void CPlayerInfo::Update(double dt)
{
	m_dElapsedTime += (float)dt;
	double mouse_diff_x, mouse_diff_y;
	MouseController::GetInstance()->GetMouseDelta(mouse_diff_x, mouse_diff_y);

	double camera_yaw = mouse_diff_x * 0.0174555555555556;		// 3.142 / 180.0
	double camera_pitch = mouse_diff_y * 0.0174555555555556;	// 3.142 / 180.0

	// If a camera is attached to this playerInfo class, then update it
	if (attachedCamera)
	{
		attachedCamera->SetCameraPos(position);
		attachedCamera->SetCameraTarget(target);
		attachedCamera->SetCameraUp(up);
	}

	// Timer
	if (b_timerDone)
	{
		elapsedTime_timer -= dt;
	}
	if (elapsedTime_timer < 0)
	{
		std::cout << "Timer countdown = 0" << std::endl;
		b_timerDone = false;
		elapsedTime_timer = 0;
	}
}
// Detect and process front / back movement on the controller
bool CPlayerInfo::Move_FrontBack(const float deltaTime, const bool direction, const float speedMultiplier)
{
	Vector3 forwardTarget = target;
	forwardTarget.y = position.y;
	Vector3 forwardVector = (forwardTarget - position).Normalized();
	Vector3 viewVector = (target - position).Normalized();
	if (direction)
	{
		if (!b_collision)
		position += forwardVector * (float)m_dSpeed * speedMultiplier * (float)deltaTime;
		//	 Constrain the position
		Constrain();
		target = position + viewVector;
	
		return true;
	}
	else
	{
		position -= forwardVector * (float)m_dSpeed * speedMultiplier *(float)deltaTime;
		//	 Constrain the position
		Constrain();
		target = position + viewVector;
	
		return true;
	}

	return false;
}
// Detect and process left / right movement on the controller
bool CPlayerInfo::Move_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier)
{
	Vector3 viewVector = target - position;
	Vector3 rightUV;
	if (direction)
	{
		rightUV = (viewVector.Normalized()).Cross(up);
		rightUV.y = 0;
		rightUV.Normalize();
		position -= rightUV * (float)m_dSpeed * speedMultiplier * deltaTime;
		Constrain();
		// Update the target
		target = position + viewVector;
		return true;
	}
	else
	{
		rightUV = (viewVector.Normalized()).Cross(up);
		rightUV.y = 0;
		rightUV.Normalize();
		position += rightUV * (float)m_dSpeed * speedMultiplier * deltaTime;
		Constrain();
		// Update the target
		target = position + viewVector;
		return true;
	}
	return false;
}

bool CPlayerInfo::Zoom_InOut(const float deltaTime, const bool direction, const float speedMultiplier)
{
	Vector3 viewVector = (target - position).Normalized();
	if (direction)
	{
		if (!b_collision)
			position += viewVector * (float)m_dSpeed * speedMultiplier * (float)deltaTime;
		//	 Constrain the position
		Constrain();
		target = position + viewVector;

		return true;
	}
	else
	{
		position -= viewVector * (float)m_dSpeed * speedMultiplier *(float)deltaTime;
		//	 Constrain the position
		Constrain();
		target = position + viewVector;

		return true;
	}

	return false;
}

// Detect and process look up / down on the controller
bool CPlayerInfo::Look_UpDown(const float deltaTime, const bool direction, const float speedMultiplier)
{
	Vector3 rightUV;
	Vector3 viewUV = (target - position).Normalized();
	rightUV = viewUV.Cross(up);
	rightUV.y = 0;
	rightUV.Normalize();
	up = rightUV.Cross(viewUV).Normalized();
	if (direction)
	{
		float pitch = (float)(m_dSpeed * speedMultiplier * (float)deltaTime);
		Mtx44 rotation;
		rotation.SetToRotation(pitch, rightUV.x, rightUV.y, rightUV.z);
		viewUV = rotation * viewUV;
		target = position + viewUV;
		return true;
	}
	else
	{
		float pitch = (float)(-m_dSpeed * speedMultiplier * (float)deltaTime);
		Mtx44 rotation;
		rotation.SetToRotation(pitch, rightUV.x, rightUV.y, rightUV.z);
		viewUV = rotation * viewUV;
		target = position + viewUV;
		return true;
	}
	return false;
}
// Detect and process look left / right on the controller
bool CPlayerInfo::Look_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier)
{
	if (speedMultiplier == 0.0f)
		return false;

	Vector3 rightUV;
	Vector3 viewUV = (target - position).Normalized();
	if (direction)
	{
		float yaw = (float)(m_dSpeed * speedMultiplier * (float)deltaTime);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		viewUV = rotation * viewUV;
		target = position + viewUV;
		rightUV = viewUV.Cross(up);
		rightUV.y = 0;
		rightUV.Normalize();
		up = rightUV.Cross(viewUV).Normalized();
		return true;
	}
	else
	{
		float yaw = (float)(-m_dSpeed * speedMultiplier * (float)deltaTime);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		viewUV = rotation * viewUV;
		target = position + viewUV;
		rightUV = viewUV.Cross(up);
		rightUV.y = 0;
		rightUV.Normalize();
		up = rightUV.Cross(viewUV).Normalized();
		return true;
	}
	return false;
}

void CPlayerInfo::ResetGame()
{

}
// Constrain the position within the borders
void CPlayerInfo::Constrain(void)
{
	// Constrain player within the boundry
	if (position.x > maxBoundary.x - 1.0f) 
	{
		position.x = maxBoundary.x - 1.0f;
	}
	if (position.y > maxBoundary.y - 1.0f)
	{
		position.y = maxBoundary.y - 1.0f;
	}
	if (position.z > maxBoundary.z - 1.0f)
	{
		position.z = maxBoundary.z - 1.0f;
	}
	if (position.x < minBoundary.x + 1.0f)
	{
		position.x = minBoundary.x + 1.0f;
	}
	if (position.y < minBoundary.y + 1.0f)
	{
		position.y = minBoundary.y + 1.0f;
	}
	if (position.z < minBoundary.z + 1.0f)
	{
		position.z = minBoundary.z + 1.0f;
	}

}

void CPlayerInfo::AttachCamera(FPSCamera* _cameraPtr)
{
	attachedCamera = _cameraPtr;
}

void CPlayerInfo::DetachCamera()
{
	attachedCamera = nullptr;
}

void CPlayerInfo::SetSpeed(double num)
{
	m_dSpeed = num;
}

double CPlayerInfo::GetSpeed()
{
	return m_dSpeed;
}