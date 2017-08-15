#ifndef MOUSE_H
#define MOUSE_H

#include "Controller.h"
#include "MouseController.h"

class CMouse :
	public CController
{
public:
	CMouse();
	virtual ~CMouse();
	// Create this controller
	virtual bool Create(CPlayerInfo* thePlayerInfo = NULL);
	// Read from the controller
	virtual int Read(const float deltaTime);

};
#endif
