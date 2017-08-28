#ifndef MOUSE_H
#define MOUSE_H

#include "Controller.h"
#include "MouseController.h"

#include "../PlayerInfo/PlayerInfo.h"
#include "../Enemy/Enemy3D.h"

class Bomb;

class CMouse :
	public CController
{ 
	Vector3 test;
	EntityBase* testTrack;

	// Selection
	Vector3 storedMiddle;
	Vector3 topLeft, botRight;

	int numberOfSelected;
	bool bMstate;
	bool bSelection;
	bool bSelected;

	//test test
	bool isZoom;
	double m_dTimer;

	void SetMouseScrollStatus(MouseController::SCROLL_TYPE _scrolltype);


public:
	CMouse();
	virtual ~CMouse();
	// Create this controller
	virtual bool Create(CPlayerInfo* thePlayerInfo = NULL);
	// Read from the controller
	virtual int Read(const float deltaTime);

	void Selection(double x, double y);
	// Setting position
	void SetTroopMovement(Bomb &BombTarget, EntityBase &IndicatorTarget);

};
#endif
