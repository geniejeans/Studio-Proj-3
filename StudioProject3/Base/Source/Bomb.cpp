#include "Bomb.h"

#include "EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "MouseController.h"
#include "MoneyManager\Money.h"
#include "GameUI\GameUI.h"
#include "SoundEngine.h"

double Bomb::m_dRate = 0;
bool Bomb::b_LMBtrue = false;

Bomb::Bomb()
	: GenericEntity(NULL)
	, defaultPosition(Vector3(0.0f, 0.0f, 0.0f))
	, defaultTarget(Vector3(0.0f, 0.0f, 0.0f))
	, defaultUp(Vector3(0.0f, 0.0f, 0.0f))
	, target(Vector3(0.0f, 0.0f, 0.0f))
	, up(Vector3(0.0f, 0.0f, 0.0f))
	, maxBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, minBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, m_pTerrain(NULL)

	, m_Scale(1, 1, 1)
	, m_dSpawnTime(10.0)
{

}

Bomb::Bomb(Mesh* _modelMesh)
{
	this->modelMesh = _modelMesh;
}

Bomb::~Bomb()
{
}

void Bomb::Render(void)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();
}

// This function will be called in EntityManager to update the bomb
void Bomb::Update(double dt)
{
	float mouse_X, mouse_Y;
	MouseController::GetInstance()->GetMousePosition(mouse_X, mouse_Y);

	if (MouseController::GetInstance()->IsButtonPressed(MouseController::LMB) && !b_LMBtrue) //if player uses bomb outside of UI, -40 points
	{
		//b_LMBtrue = true;
		SetBombActive(true);	
		if (mouse_X > 0.f && mouse_X < 800.f
			&& mouse_Y < 493.f && mouse_Y > 0.f && GameUI::GetInstance()->GetBombRender())
		{
			CSoundEngine::GetInstance()->Init();
			CSoundEngine::GetInstance()->AddSound("BombExplode", "Image//Sounds/Bomb_Exploding.mp3");
			CSoundEngine::GetInstance()->PlayASound("BombExplode", false);

	//		Money::GetInstance()->SetActiveDestroyed(true);
			if(Money::GetInstance()->GetMoney() > 40)
			Money::GetInstance()->DeductMoney(40);
		}
	}
	else if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB) && b_LMBtrue)
	{
		//b_LMBtrue = false;
		SetBombActive(false);

	}
	//cout << b_LMBtrue << endl;
}

bool Bomb::GetBombActive()
{
	return b_LMBtrue;
}

void Bomb::SetBombActive(bool IsTrue)
{
	b_LMBtrue = IsTrue;
}

Bomb* Create::Bomb3D(const std::string& _meshName,
	const Vector3& _position,
	const Vector3& _scale)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	Bomb* result = new Bomb(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);

	result->SetCollider(true);
	result->SetMeshName(_meshName);

	// Set collision
	result->SetAABB(Vector3(_position.x + result->GetScale().x,
		_position.y + result->GetScale().y,
		_position.z + result->GetScale().z),
		Vector3(-_position.x - result->GetScale().x,
			_position.y - result->GetScale().y,
			_position.z - result->GetScale().z));

	EntityManager::GetInstance()->AddBombEntity(result);
	return result;
}