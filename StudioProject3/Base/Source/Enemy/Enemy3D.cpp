#include "Enemy3D.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"

CEnemy3D::CEnemy3D(Mesh* _modelMesh)
	: GenericEntity(NULL)
	, defaultPosition(Vector3(0.0f,0.0f,0.0f))
	, defaultTarget(Vector3(0.0f, 0.0f, 0.0f))
	, defaultUp(Vector3(0.0f, 0.0f, 0.0f))
	, target(Vector3(0.0f, 0.0f, 0.0f))
	, up(Vector3(0.0f, 0.0f, 0.0f))
	, maxBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, minBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, m_pTerrain(NULL)
	, m_fElapsedTimeBeforeUpdate(0.0f)
	, rotate(0.0)
	, m_bChangeDir(false)
	, m_bFireProjectile(false)

{
	this->modelMesh = _modelMesh;
}


CEnemy3D::~CEnemy3D()
{
}

void CEnemy3D::Init(void)
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
}

// Reset this player instance to default
void CEnemy3D::Reset(void)
{
	// Set the current values to default values
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}
void CEnemy3D::ResetGame()
{

}
// Set position
void CEnemy3D::SetPos(const Vector3& pos)
{
	position = pos;
}

// Set target
void CEnemy3D::SetTarget(const Vector3& target)
{
	this->target = target;
}
// Set Up
void CEnemy3D::SetUp(const Vector3& up)
{
	this->up = up;
}
// Set the boundary for the player info
void CEnemy3D::SetBoundary(Vector3 max, Vector3 min)
{
	maxBoundary = max;
	minBoundary = min;
}
// Set the terrain for the player info
void CEnemy3D::SetTerrain(GroundEntity* m_pTerrain)
{
	if (m_pTerrain != NULL)
	{
		this->m_pTerrain = m_pTerrain;

		SetBoundary(this->m_pTerrain->GetMaxBoundary(), this->m_pTerrain->GetMinBoundary());
	}
}

void CEnemy3D::SetMesh(Mesh* mesh)
{
	this->modelMesh = mesh;
}

void CEnemy3D::SetType(int type)
{
	switch (type)
	{
	case 1:
		this->type = CENEMY3D_TYPE::TROOP;
		break;
	case 2:
		this->type = CENEMY3D_TYPE::TURRET;
		break;
	default:
		break;
	}
}

void CEnemy3D::SetDestination(Vector3 destination)
{
	this->destination = destination;
	finalDestination = destination;
}

// Get position
Vector3 CEnemy3D::GetPos(void) const
{
	return position;
}

// Get target
Vector3 CEnemy3D::GetTarget(void) const
{
	return target;
}
// Get Up
Vector3 CEnemy3D::GetUp(void) const
{
	return up;
}
// Get the terrain for the player info
GroundEntity* CEnemy3D::GetTerrain(void)
{
	return m_pTerrain;
}

// Update
void CEnemy3D::Update(double dt)
{
	// If enemy is turret.
	if (type == CENEMY3D_TYPE::TURRET && m_bFireProjectile)
	{
		rotate = (fireDestination - position).Normalized();
		Vector3 newPos = position;
		newPos.x += rotate.x * 20.f;
		newPos.z += rotate.z * 20.f;
		newPos.y += 17.f;
		CProjectile* aProjectile = Create::Projectile("Troopbullet", newPos, (fireDestination - newPos).Normalized(), 4.0f, 100.0f, this);
		aProjectile->SetCollider(true);
		aProjectile->SetFireDestination(fireDestination);
		m_bFireProjectile = false;
		return;
	}

	if (type == CENEMY3D_TYPE::TROOP && !m_bActionDone)
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
				position += viewVector * (float)m_dSpeed * (float)dt;

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
	else if (type == CENEMY3D_TYPE::TROOP && m_bActionDone && m_bFireProjectile)
	{
		rotate = (fireDestination - position).Normalized();
		CProjectile* aProjectile = Create::Projectile("Troopbullet", position, (fireDestination - position).Normalized(), 4.0f,100.0f,this);
		aProjectile->SetCollider(true);
		aProjectile->SetFireDestination(fireDestination);
		m_bFireProjectile = false;
	}
}

// Constrain the position within the borders
void CEnemy3D::Constrain(void)
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
void CEnemy3D::Render(void)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	if (type != CENEMY3D_TYPE::TURRET)
	{
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, position.z);
		modelStack.Rotate(Math::RadianToDegree(atan2(rotate.x, rotate.z)), 0, 1, 0);
		modelStack.Scale(scale.x, scale.y, scale.z);
		RenderHelper::RenderMesh(modelMesh);
		modelStack.PopMatrix();
	}

	else
	{
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, position.z);
		modelStack.Scale(scale.x, scale.y, scale.z);
		modelStack.PushMatrix();
		modelStack.Rotate(Math::RadianToDegree(atan2(rotate.x, rotate.z)), 0, 1, 0);
		modelStack.Translate(0, 0, -1);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Rotate(-20, 0, 0, 1);
		RenderHelper::RenderMesh(modelMesh);
		modelStack.PopMatrix();
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("turretBot"));
		modelStack.PopMatrix();
	}

}

CEnemy3D* Create::Enemy3D(const std::string& _meshName,
						const Vector3& _position,
						const Vector3& _scale,
						const int type)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	CEnemy3D* result = new CEnemy3D(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);
	result->SetCollider(true);
	result->SetMeshName(_meshName);
//	EntityManager::GetInstance()->AddEntity(result);
	if (type == 1)
		EntityManager::GetInstance()->AddTroopEntity(result);
	else if (type == 2)
		EntityManager::GetInstance()->AddTurretEntity(result);
	return result;
}