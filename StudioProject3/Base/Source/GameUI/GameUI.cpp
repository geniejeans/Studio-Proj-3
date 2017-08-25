#include "GameUI.h"
#include "MouseController.h"
#include "../Enemy/Enemy3D.h"
#include "../Enemy/RadarScan.h"
#include "../MoneyManager/Money.h"
#include <iostream>
bool GameUI::m_bIsRendered = false;

void GameUI::Update(GroundEntity *groundEntity)
{
	float mouse_X, mouse_Y;
	MouseController::GetInstance()->GetMousePosition(mouse_X, mouse_Y);
//	std::cout << mouse_X << " and " << mouse_Y << std::endl;
//	std::cout << mouse_X - 800 / 2 << " and " << mouse_Y - 500 / 2 << std::endl;
	if (MouseController::GetInstance()->IsButtonPressed(MouseController::LMB))
	{
		if (mouse_X > 5.f && mouse_X < 170.f
			&& mouse_Y > 504.f && mouse_Y < 545.f)
		{
			if (!RadarScan::GetInstance()->GetCooldown())
				RadarScan::GetInstance()->SetRPressed(true);
		}
		else if (mouse_X > 180.f && mouse_X < 280.f
			&& mouse_Y > 500.f && mouse_Y < 590.f)
		{
			//do bomb
			if (GetBombRender())
				SetBombRender(false);
			else
				SetBombRender(true);
		}

		else if (mouse_X > 295.f && mouse_X < 395.f
			&& mouse_Y > 500.f && mouse_Y < 590.f)
		{
			//do shield
			SetBombRender(false);

		}
		else if (mouse_X > 410.f && mouse_X < 510.f
			&& mouse_Y > 500.f && mouse_Y < 590.f)
		{
			SetBombRender(false);

			CEnemy3D* newTroop;
			newTroop = Create::Enemy3D("testTroop", Vector3(Math::RandFloatMinMax(-60.f, 60.f), 10, Math::RandFloatMinMax(360.f, 380.f)), Vector3(1, 1, 1));
			newTroop->Init();
			newTroop->SetTerrain(groundEntity);
			newTroop->SetType(1);
			newTroop->SetDestination(Vector3(0, 10, 0));
			Money::GetInstance()->DeductMoney(10);
		}
	}
}

bool GameUI::GetBombRender()
{
	return m_bIsRendered;
}

void GameUI::SetBombRender(bool IsRendered)
{
	m_bIsRendered = IsRendered;
}