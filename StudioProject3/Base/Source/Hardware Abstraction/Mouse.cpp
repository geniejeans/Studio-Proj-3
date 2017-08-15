#include "Mouse.h"
using namespace std;
#include "../PlayerInfo/PlayerInfo.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

// Create this controller
bool CMouse::Create(CPlayerInfo* thePlayerInfo)
{
	CController::Create(thePlayerInfo);
	return false;
}


// Read from the controller
int CMouse::Read(const float deltaTime)
{
	CController::Read(deltaTime);
	double mouse_diff_x, mouse_diff_y;
	MouseController::GetInstance()->GetMouseDelta(mouse_diff_x, mouse_diff_y);

	// Process the keys for customisation
	return 0;
}