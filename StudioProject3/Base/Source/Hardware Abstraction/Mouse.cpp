#include "Mouse.h"
#include "../PlayerInfo/PlayerInfo.h"
#include "../Application.h"
#include "../EntityManager.h"
#include "../Bomb.h"
#include "GL/glew.h"
#include "GLFW\glfw3.h"

CMouse::CMouse()
	: numberOfSelected(0)
	, bMstate(false)
	, bSelection(false)
	, bSelected(false)
	, topLeft(0.f, 0.f, 0.f)
	, botRight(0.f, 0.f, 0.f)
	, m_dTimer(0.5)
	, isZoom(false)
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

void CMouse::SetMouseScrollStatus(MouseController::SCROLL_TYPE _scrolltype)
{
	if (_scrolltype == 1)
	{
		MouseController::GetInstance()->yoffset = 0;
	}
}

// Read from the controller
int CMouse::Read(const float deltaTime)
{
	CController::Read(deltaTime);

	// Get window coords
	double x, y;
	MouseController::GetInstance()->GetMousePosition(x, y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	
	m_dTimer -= deltaTime;
	Zoom_InOut(deltaTime, true,
		(float)MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET));
	
	
	if (m_dTimer <= 0.0)
	{
		m_dTimer = 0.5;
		SetMouseScrollStatus(MouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET);
	}

	//if (MouseController::GetInstance()->IsButtonDown(MouseController::LMB)
	//	&& y < h  * 0.833)
	//{
	//	// Generate white quad
	//	//Selection(x, y);

	//	// Set destination of troops
	//	SetTroopsDestination(x, y, w, h);
	//}
	//
	
	return 1;
}

// Generate selection quad
void CMouse::Selection(double x, double y)
{
	//double storeX, storeY; //store click coordinates
	//float scaleX, scaleY; //size of white quad

	//// When holding
	//if (MouseController::GetInstance()->IsButtonPressed(MouseController::LMB))
	//{
	//	//store when button pressed coords
	//	MouseController::GetInstance()->GetMousePosition(storeX, storeY);
	//	cout << storeX << " | " << storeY << endl;

	//	//drag mouse
	//	if (MouseController::GetInstance()->IsButtonDown(MouseController::LMB))
	//	{

	//	}
	//	
	//}
	//
	//cout << x << " | " << y << endl;
}

void CMouse::SetTroopMovement(Bomb &BombTarget, EntityBase &IndicatorTarget, Vector3 &mousePos)
{
	float mouse_X, mouse_Y;
	MouseController::GetInstance()->GetMousePosition(mouse_X, mouse_Y);
	// Get normalised device space coords
	float x = (2.0f * mouse_X) / 800.f - 1.0f;
	float y = 1.0f - (2.0f * mouse_Y) / 600.f;
	float z = 1.0f;
	Vector3 ray_nds = Vector3(x, y, z);

	// Get Homogeneous Clip Space Coords
	Vector3 ray_clip = Vector3(ray_nds.x, ray_nds.y, -1.0f);

	// Get Eye (Camera) Coords
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	Vector3 ray_eye = perspective.GetInverse() * ray_clip;
	ray_eye = Vector3(ray_eye.x, ray_eye.y, -1.0f);

	// Get World Coords
	Vector3 ray_wor = thePlayerInfo->GetCamera()->GetViewMatrix().GetInverse() * ray_eye;
	ray_wor = ray_wor.Normalize();

	//Testing of ray
	float distanceFromRay = -(thePlayerInfo->GetPos().Dot(Vector3(0, 1, 0) + 0) / ray_wor.Dot(Vector3(0, 1, 0))) - 20.f;
	mousePos = Vector3(thePlayerInfo->GetPos().x + ray_wor.x * distanceFromRay, 10.f, thePlayerInfo->GetPos().z + ray_wor.z * distanceFromRay);

	//troop selection
	if (mouse_Y < 500)
	{
		if (!bMstate && MouseController::GetInstance()->IsButtonDown(MouseController::LMB))
		{
			bMstate = true;
			topLeft = mousePos;
		}
		if (MouseController::GetInstance()->IsButtonDown(MouseController::LMB) && (BombTarget.GetPosition().y != 10.f))
		{
			IndicatorTarget.SetPosition(Vector3(topLeft.x + (mousePos.x - topLeft.x) / 2, 10, topLeft.z + (mousePos.z - topLeft.z) / 2));
			IndicatorTarget.SetScale(Vector3(abs(mousePos.x - topLeft.x) / 2, 10, abs(mousePos.z - topLeft.z) / 2));
		}
		if (bMstate && !MouseController::GetInstance()->IsButtonDown(MouseController::LMB))
		{
			botRight = mousePos;
			bMstate = false;
			bSelection = true;
		}

		if (bSelection && (topLeft != botRight))
		{
			if (topLeft != botRight)
			{
				numberOfSelected = 0;
				bSelected = false;
			}
			std::list<EntityBase*> list = EntityManager::GetInstance()->GetTroopList();
			std::list<EntityBase*>::iterator it;
			for (it = list.begin(); it != list.end(); ++it)
			{
				(*it)->SetSelected(false);
				if (((*it)->GetPosition().x > topLeft.x && (*it)->GetPosition().x < botRight.x)
					&& ((*it)->GetPosition().z > topLeft.z && (*it)->GetPosition().z < botRight.z))
				{
					(*it)->SetSelected(true);
					bSelected = true;
					numberOfSelected++;
				}
			}
			bSelection = false;
		}
		if (numberOfSelected != 0 && !topLeft.IsZero() && (topLeft == botRight))
		{
			IndicatorTarget.SetPosition(mousePos);
			IndicatorTarget.SetScale(Vector3(10, 10, 10));
			std::list<EntityBase*> list = EntityManager::GetInstance()->GetTroopList();
			vector<Vector3>estimatedDestination;
			std::list<EntityBase*>::iterator it;

			for (int i = 0; i < numberOfSelected; i++)
			{
				bool tooClose = false;
				estimatedDestination.push_back(Vector3(topLeft.x, 10, topLeft.z));
				do
				{
					tooClose = false;
					for (int x = 0; x < i; x++)
					{
						if ((estimatedDestination[i] - estimatedDestination[x]).Length() < 5)
						{
							tooClose = true;
							estimatedDestination[i].Set(estimatedDestination[i].x + Math::RandFloatMinMax(-10, 10), 10, estimatedDestination[i].z + Math::RandFloatMinMax(-10, 10));
						}
					}
				} while (tooClose);
			}
			int i = 0;
			for (it = list.begin(); it != list.end(); ++it)
			{
				if ((*it)->GetSelected())
				{
					(*it)->SetDestination(Vector3(estimatedDestination[i].x, 10, estimatedDestination[i].z));
					(*it)->SetActionDone(false);
					(*it)->SetSelected(false);
					i++;
				}
			}
			numberOfSelected = 0;
			bSelected = false;
		}
	}
}