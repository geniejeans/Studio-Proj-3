#include "Troop3D.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "KeyboardController.h"

CTroop3D::CTroop3D(Mesh* _modelMesh)
	: GenericEntity(NULL)
	, defaultPosition(Vector3(0.0f, 0.0f, 0.0f))
	, defaultTarget(Vector3(0.0f, 0.0f, 0.0f))
	, defaultUp(Vector3(0.0f, 0.0f, 0.0f))
	, target(Vector3(0.0f, 0.0f, 0.0f))
	, up(Vector3(0.0f, 0.0f, 0.0f))
	, maxBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, minBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, m_pTerrain(NULL)
	, m_fElapsedTimeBeforeUpdate(0.0f)
	, rotate(0.0f)
	, m_bChangeDir(false)
	, m_bFireProjectile(false)

{
	this->modelMesh = _modelMesh;
}


CTroop3D::~CTroop3D()
{
}

void CTroop3D::Init(void)
{
	// Set the default values
	//	defaultPosition.Set(0, 0, 10);
	defaultTarget.Set(0, 0, 0);
	defaultUp.Set(0, 1, 0);

	// Set the current values
	//	position.Set(10.0f, 0.0f, 0.0f);
	//	target.Set(position.x, position.y, 450.0f);
	target.Set(0, 0, 0);
	up.Set(0.0f, 1.0f, 0.0f);

	// Set Boundary
	maxBoundary.Set(1, 1, 1);
	minBoundary.Set(-1, -1, -1);

	// Set speed
	m_dSpeed = 10.0;

	//m_bIsRendered = true;
}

// Reset this player instance to default
void CTroop3D::Reset(void)
{
	// Set the current values to default values
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}
void CTroop3D::ResetGame()
{

}
// Set position
void CTroop3D::SetPos(const Vector3& pos)
{
	position = pos;
}

// Set target
void CTroop3D::SetTarget(const Vector3& target)
{
	this->target = target;
}
// Set Up
void CTroop3D::SetUp(const Vector3& up)
{
	this->up = up;
}
// Set the boundary for the player info
void CTroop3D::SetBoundary(Vector3 max, Vector3 min)
{
	maxBoundary = max;
	minBoundary = min;
}
// Set the terrain for the player info
void CTroop3D::SetTerrain(GroundEntity* m_pTerrain)
{
	if (m_pTerrain != NULL)
	{
		this->m_pTerrain = m_pTerrain;

		SetBoundary(this->m_pTerrain->GetMaxBoundary(), this->m_pTerrain->GetMinBoundary());
	}
}

void CTroop3D::SetMesh(Mesh* mesh)
{
	this->modelMesh = mesh;
}

void CTroop3D::SetType(int type)
{
	switch (type)
	{
	case 1:
		this->type = CTROOP3D_TYPE::TROOPER;
		break;
	case 2:
		this->type = CTROOP3D_TYPE::ARCHER;
		break;
	case 3:
		this->type = CTROOP3D_TYPE::TANKER;
		break;
	default:
		break;
	}
}

void CTroop3D::SetDestination(Vector3 destination)
{
	this->destination = destination;
	finalDestination = destination;
}

// Get position
Vector3 CTroop3D::GetPos(void) const
{
	return position;
}

// Get target
Vector3 CTroop3D::GetTarget(void) const
{
	return target;
}
// Get Up
Vector3 CTroop3D::GetUp(void) const
{
	return up;
}
// Get the terrain for the player info
GroundEntity* CTroop3D::GetTerrain(void)
{
	return m_pTerrain;
}

// Update
void CTroop3D::Update(double dt)
{
	if (!m_bActionDone)
	{
		//This is for collision with turrets
		if (!m_bCollide)
		{
			destination = finalDestination;
			target = destination;
		}

		//Make sure that this can also collide with turrets
		//If troop is not at the selected position
		if ((position - destination).Length() > 1.0f)
		{
			rotate = (destination - position).Normalized();
			Vector3 viewVector = (target - position).Normalized();
			if (m_fBuffer == 0)
			{
				m_bChangeDir = false;
			}

			if (!m_bCollide || m_bChangeDir)
				position += viewVector * (float)m_dSpeed * (float)dt * 1.5;

			else
			{
				Vector3 viewVector = (target - position).Normalized();
				Vector3 backwardPosition = position;
				backwardPosition -= viewVector * (float)(m_dSpeed * 2);
				Vector3 laterPosition = position; Vector3 laterPosition2 = position;

				Vector3 newPosLeft = backwardPosition.Cross(objAvoidPos);
				Vector3 newPosRight = objAvoidPos.Cross(backwardPosition);

				laterPosition += (newPosLeft - position).Normalized();
				laterPosition2 += (newPosRight - position).Normalized();

				//check dist between troop and the thing that it is trying to avoid
				if ((newPosLeft - objAvoidPos).LengthSquared() < (newPosRight - objAvoidPos).LengthSquared())
					target = Vector3(newPosRight.x, destination.y, newPosRight.z);
				else
					target = Vector3(newPosLeft.x, destination.y, newPosLeft.z);

				m_bChangeDir = true;
			}
		}

		else if ((position - finalDestination).Length() < 1.0f)
			m_bActionDone = true;
		// Constrain the position
		Constrain();
	}
	else if (m_bActionDone && m_bFireProjectile)
	{
		rotate = (fireDestination - position).Normalized();
		if (type == CTROOP3D_TYPE::TROOPER)
		{
			CProjectile* aProjectile = Create::Projectile("Troopbullet", position, (fireDestination - position).Normalized(), 4.0f, 100.0f, 1, 1, this);
			aProjectile->SetCollider(true);
			aProjectile->SetFireDestination(fireDestination);
			m_bFireProjectile = false;
		}
		else if (type == CTROOP3D_TYPE::ARCHER)
		{
			Vector3 velocity = (fireDestination - position).Normalized() * 2.5;
			velocity.y = (fireDestination - position).Length() / 2;
			CProjectile* aProjectile = Create::Projectile("Troopbullet", position, (fireDestination - position).Normalized(), 4.0f, 20.0f, 1, 5, this);
			if (velocity.y > 40.f)
				aProjectile->SetSpeed(10.0f);
			aProjectile->SetCollider(true);
			aProjectile->SetFireDestination(fireDestination);
			aProjectile->SetVelocity(velocity);
			m_bFireProjectile = false;
		}
		else
		{
			CProjectile* aProjectile = Create::Projectile("Troopbullet", position, (fireDestination - position).Normalized(), 4.0f, 100.0f, 1, 3, this);
			aProjectile->SetCollider(true);
			aProjectile->SetFireDestination(fireDestination);
			m_bFireProjectile = false;
		}

	}
}

// Constrain the position within the borders
void CTroop3D::Constrain(void)
{
	// Constrain player within the boundary
	if (position.x > maxBoundary.x - 1.0f)
		position.x = maxBoundary.x - 1.0f;
	if (position.z > maxBoundary.z - 1.0f)
		position.z = maxBoundary.z - 1.0f;
	if (position.x < minBoundary.x + 1.0f)
		position.x = minBoundary.x + 1.0f;
	if (position.z < minBoundary.z + 1.0f)
		position.z = minBoundary.z + 1.0f;

	// if the y position is not equal to terrain height at that position, 
	// then update y position to the terrain height
	if (position.y <= m_pTerrain->GetTerrainHeight(position))
		position.y = m_pTerrain->GetTerrainHeight(position);
}

// Render
void CTroop3D::Render(void)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Rotate(Math::RadianToDegree(atan2(rotate.x, rotate.z)), 0, 1, 0);
	modelStack.Scale(scale.x, scale.y, scale.z);
	//Render health bar===
	modelStack.PushMatrix();
	modelStack.Translate(0, scale.y + 10.f, 0);
	modelStack.Scale(m_iHealth / 5.f, 0.5f, 1.f);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("healthG"));
	modelStack.PopMatrix();
	//Render if selected==
	if (m_bSelected)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, -1, 0);
		modelStack.Scale(5,5,5);
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("IndicatorSelect"));
		modelStack.PopMatrix();
	}
	//====================
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();
}

CTroop3D* Create::Troop3D(const std::string& _meshName,
	const Vector3& _position,
	const Vector3& _scale,
	const int type)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	CTroop3D* result = new CTroop3D(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);
	result->SetCollider(true);
	result->SetMeshName(_meshName);
	switch (type)
	{
	case 1:
		result->SetRange(60 * 60);
		result->SetHealth(50);
		result->SetType(1);
		break;
	case 2:
		result->SetRange(100 * 100);
		result->SetHealth(50);
		result->SetType(2);
		break;
	case 3:
		result->SetRange(40 * 40);
		result->SetHealth(80);
		result->SetType(3);
		break;
	default:
		break;
	}
	EntityManager::GetInstance()->AddTroopEntity(result);
	return result;
}