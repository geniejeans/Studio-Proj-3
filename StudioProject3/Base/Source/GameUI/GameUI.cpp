#include "GameUI.h"
#include "MouseController.h"
#include "../Enemy/Enemy3D.h"
#include <iostream>

void GameUI::Update(GroundEntity *groundEntity)
{
	float mouse_X, mouse_Y;
	MouseController::GetInstance()->GetMousePosition(mouse_X, mouse_Y);
//	std::cout << mouse_X << " and " << mouse_Y << std::endl;
//	std::cout << mouse_X - 800 / 2 << " and " << mouse_Y - 500 / 2 << std::endl;
	if (MouseController::GetInstance()->IsButtonPressed(MouseController::LMB))
	{
		if (mouse_X > 180.f && mouse_X < 280.f
			&& mouse_Y > 500.f && mouse_Y < 590.f)
		{
			//do bomb
		}

		else if (mouse_X > 295.f && mouse_X < 395.f
			&& mouse_Y > 500.f && mouse_Y < 590.f)
		{
			//do shield
		}
		else if (mouse_X > 410.f && mouse_X < 510.f
			&& mouse_Y > 500.f && mouse_Y < 590.f)
		{
			CEnemy3D* newTroop;
			newTroop = Create::Enemy3D("testTroop", Vector3(Math::RandFloatMinMax(-60.f, 60.f), 10, Math::RandFloatMinMax(400.f, 410.f)), Vector3(1, 1, 1));
			newTroop->Init();
			newTroop->SetTerrain(groundEntity);
			newTroop->SetType(1);
			newTroop->SetDestination(Vector3(0, 10, 0));
		}
	}
}