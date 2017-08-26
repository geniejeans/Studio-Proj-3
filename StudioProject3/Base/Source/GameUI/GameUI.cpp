#include "GameUI.h"
#include "MouseController.h"
#include "../Enemy/Enemy3D.h"
#include "../Enemy/Troop3D.h"
#include "../Enemy/RadarScan.h"
#include "../MoneyManager/Money.h"
#include "../Enemy/Shield.h"
#include <iostream>
bool GameUI::m_bIsRendered = false;
bool GameUI::m_bShieldIsPressed = false;

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
			if (Money::GetInstance()->GetMoney() >= Money::GetInstance()->GetShieldPriceRate())
			{
				cout << "The current price is now " << Money::GetInstance()->GetShieldPriceRate() << " coins." << endl;

				//set shield to true
				Shield::GetInstance()->SetShieldActive();

				// Money Decreases every use of shield.
				Money::GetInstance()->SetMoney(Money::GetInstance()->GetMoney() - Money::GetInstance()->GetShieldPriceRate());

				// Setting a limit for the price of Shield
				if (Money::GetInstance()->GetShieldPriceRate() < 150)//increase shield rate
				{
					// Increase the Rate every use of shield.
					Money::GetInstance()->SetShieldPriceRate(Money::GetInstance()->GetShieldPriceRate() + 10);
				}
				else // If the price of Shield is 100, then the price will always be at 100.
				{
					Money::GetInstance()->SetShieldPriceRate(150);
				}

			}
			else
			{
				cout << "You do not have enough to pay " << Money::GetInstance()->GetShieldPriceRate() << " coins." << endl;
			}

		}
		else if (mouse_X > 410.f && mouse_X < 510.f
			&& mouse_Y > 500.f && mouse_Y < 590.f)
		{
			SetBombRender(false);

			CTroop3D* newTroop;
			newTroop = Create::Troop3D("testTroop", Vector3(Math::RandFloatMinMax(-60.f, 60.f), 10, Math::RandFloatMinMax(360.f, 380.f)), Vector3(1, 1, 1), 1);
			newTroop->Init();
			newTroop->SetTerrain(groundEntity);
			newTroop->SetDestination(Vector3(0, 10, 0));
			Money::GetInstance()->DeductMoney(10);
		}

		else if (mouse_X > 525.f && mouse_X < 625.f
			&& mouse_Y > 500.f && mouse_Y < 590.f)
		{
			SetBombRender(false);

			CTroop3D* newTroop;
			newTroop = Create::Troop3D("testTroop2", Vector3(Math::RandFloatMinMax(-60.f, 60.f), 10, Math::RandFloatMinMax(360.f, 380.f)), Vector3(1, 1, 1), 2);
			newTroop->Init();
			newTroop->SetTerrain(groundEntity);
			newTroop->SetDestination(Vector3(0, 10, 0));
			Money::GetInstance()->DeductMoney(20);
		}

		else if (mouse_X > 640.f && mouse_X < 740.f
			&& mouse_Y > 500.f && mouse_Y < 590.f)
		{
			SetBombRender(false);

			CTroop3D* newTroop;
			newTroop = Create::Troop3D("testTroop3", Vector3(Math::RandFloatMinMax(-60.f, 60.f), 10, Math::RandFloatMinMax(360.f, 380.f)), Vector3(1, 1, 1), 3);
			newTroop->Init();
			newTroop->SetTerrain(groundEntity);
			newTroop->SetDestination(Vector3(0, 10, 0));
			Money::GetInstance()->DeductMoney(30);
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

// Set the Boolean for Shield.
void GameUI::SetShieldIsPressed(bool is_True)
{
	m_bShieldIsPressed = is_True;
}
// Get the Boolean for Shield.
bool GameUI::GetShieldIsPressed()
{
	return m_bShieldIsPressed;
}