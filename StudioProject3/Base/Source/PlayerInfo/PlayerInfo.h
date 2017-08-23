#pragma once
#include "Vector3.h"
#include "../FPSCamera.h"
#include "../GroundEntity.h"
#include <string>

class CPlayerInfo
{
protected:
	static CPlayerInfo *s_instance;
	CPlayerInfo(void);

public:
	static CPlayerInfo *GetInstance()
	{
		if (!s_instance)
			s_instance = new CPlayerInfo;
		return s_instance;
	}
	static bool DropInstance()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = NULL;
			return true;
		}
		return false;
	}
	~CPlayerInfo(void);

	// Initialise this class instance
	void Init(void);
	// Reset this player instance to default
	void Reset(void);

	// Set position
	void SetPos(const Vector3& pos);
	// Set target
	void SetTarget(const Vector3& target);
	// Set Up
	void SetUp(const Vector3& up);
	// Set the boundary for the player info
	void SetBoundary(Vector3 max, Vector3 min);
	// Set the terrain for the player info
	void SetTerrain(GroundEntity* m_pTerrain);

	// Get position
	Vector3 GetPos(void) const;
	// Get target
	Vector3 GetTarget(void) const;
	// Get Up
	Vector3 GetUp(void) const;
	// Update
	void Update(double dt = 0.0333f);

	// Constrain the position within the borders
	void Constrain(void);

	// Handling Camera
	void AttachCamera(FPSCamera* _cameraPtr);
	void DetachCamera();
	FPSCamera *GetCamera() { return attachedCamera; };
	//Setting m_speed
	void SetSpeed(double num);
	double GetSpeed();
// Detect and process front / back movement on the controller
	bool Move_FrontBack(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	// Detect and process left / right movement on the controller
	bool Move_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	// Detect and process zoom in / out on the controller
	bool Zoom_InOut(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	// Detect and process look up / down on the controller
	bool Look_UpDown(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	// Detect and process look left / right on the controller
	bool Look_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	// Setting collision for player 
	void SetCollision(bool collide);
	//Reset 
	void ResetGame();

	// Timer
	bool b_timerDone;
	double d_TimeCountdown;
	double elapsedTime_timer;
	virtual void SetTimeCountdown(const double d_TimeCountdown);
private:
	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 position, target, up;
	Vector3 maxBoundary, minBoundary;
	GroundEntity* m_pTerrain;

	FPSCamera* attachedCamera;

	double m_dSpeed;
	double m_dElapsedTime;
	bool b_collision; 
};
