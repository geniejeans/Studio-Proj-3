#include "Ninja3D.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "KeyboardController.h"
#include "RadarScan.h"
#include "../MoneyManager/Money.h"

bool CNinja3D::m_bIsRendered = true;
bool CNinja3D::isRpressed = false;

CNinja3D::CNinja3D(Mesh* _modelMesh)
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
	, stealDelay(0.0f)
	, m_bChangeDir(false)
	, m_bFireProjectile(false)
	, m_bRealRendered(true)
	, m_bRadarActive(false)

{
	this->modelMesh = _modelMesh;
}


CNinja3D::~CNinja3D()
{
}

void CNinja3D::Init(void)
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
void CNinja3D::Reset(void)
{
	// Set the current values to default values
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}
void CNinja3D::ResetGame()
{

}
// Set position
void CNinja3D::SetPos(const Vector3& pos)
{
	position = pos;
}

// Set target
void CNinja3D::SetTarget(const Vector3& target)
{
	this->target = target;
}
// Set Up
void CNinja3D::SetUp(const Vector3& up)
{
	this->up = up;
}
// Set the boundary for the player info
void CNinja3D::SetBoundary(Vector3 max, Vector3 min)
{
	maxBoundary = max;
	minBoundary = min;
}
// Set the terrain for the player info
void CNinja3D::SetTerrain(GroundEntity* m_pTerrain)
{
	if (m_pTerrain != NULL)
	{
		this->m_pTerrain = m_pTerrain;

		SetBoundary(this->m_pTerrain->GetMaxBoundary(), this->m_pTerrain->GetMinBoundary());
	}
}

void CNinja3D::SetMesh(Mesh* mesh)
{
	this->modelMesh = mesh;
}

void CNinja3D::SetDestination(Vector3 destination)
{
	this->destination = destination;
	finalDestination = destination;
}

// Get position
Vector3 CNinja3D::GetPos(void) const
{
	return position;
}

// Get target
Vector3 CNinja3D::GetTarget(void) const
{
	return target;
}
// Get Up
Vector3 CNinja3D::GetUp(void) const
{
	return up;
}
// Get the terrain for the player info
GroundEntity* CNinja3D::GetTerrain(void)
{
	return m_pTerrain;
}

// Update
void CNinja3D::Update(double dt)
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
				position += viewVector * (float)m_dSpeed * (float)dt;

			else
			{
				Vector3 viewVector = (target - position).Normalized();
				Vector3 backwardPosition = position;
				backwardPosition -= viewVector * (float)(m_dSpeed * 2);

				Vector3 newPosLeft = backwardPosition.Cross(objAvoidPos);
				Vector3 newPosRight = objAvoidPos.Cross(backwardPosition);

				//check dist between troop and the thing that it is trying to avoid
				if ((newPosLeft - position) < (newPosRight - position))
					target = Vector3(newPosRight.x, destination.y, newPosRight.z);
				else
					target = Vector3(newPosLeft.x, destination.y, newPosLeft.z);

				m_bChangeDir = true;
			}
		}

		else if ((position - finalDestination).Length() < 1.0f)
		{
			rotate = (Vector3(0, 10, 400) - position).Normalized();
			m_bActionDone = true;
		}

		// Constrain the position
		Constrain();
	}

	{
		if (m_iHealth == 30 && (position.z > -390.f && position.z < 330.f))
		{
			//If radar is active
			if (RadarScan::GetInstance()->GetRPressed())
			{
				RenderDelay += dt;
				if (RenderDelay >= 0.3f)
				{
					if (m_bRadarActive)
						m_bRadarActive = false;
					else
						m_bRadarActive = true;
					RenderDelay = 0.0f;
				}
				//radar
				if (!m_bRadarActive) // Replace with Radar here!
				{
					SetEnemyRender(true);
				}
				else if (m_bRadarActive)
				{
					SetEnemyRender(false);
				}
				m_bRealRendered = m_bIsRendered;
			}
			//If radar is not active
			else
				m_bRealRendered = false;
		}
		//Only show ninjas if near bases
		else
			m_bRealRendered = true;
		if (m_bActionDone)
		{
			stealDelay += dt;
			if (stealDelay >= 3.0f)
			{
				Money::GetInstance()->DeductMoney(Math::RandIntMinMax(5, 10));
				stealDelay = 0.0f;
			}
		}
	}
	
}

bool CNinja3D::GetEnemyRender()
{
	return m_bIsRendered;
}

void CNinja3D::SetEnemyRender(bool IsRendered)
{
	m_bIsRendered = IsRendered;
}

// Constrain the position within the borders
void CNinja3D::Constrain(void)
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
void CNinja3D::Render(void)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	if (m_bRealRendered)
	{
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, position.z);
		modelStack.Rotate(Math::RadianToDegree(atan2(rotate.x, rotate.z)), 0, 1, 0);
		modelStack.Scale(scale.x, scale.y, scale.z);
		modelStack.PushMatrix();
		modelStack.Translate(0, scale.y + 10, 0);
		modelStack.Scale(m_iHealth / 5, 0.5, 1);
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("healthR"));
		modelStack.PopMatrix();
		RenderHelper::RenderMesh(modelMesh);
		RenderHelper::RenderMesh(modelMesh);
		modelStack.PopMatrix();
	}
}

CNinja3D* Create::Ninja3D(const std::string& _meshName,
	const Vector3& _position,
	const Vector3& _scale)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	CNinja3D* result = new CNinja3D(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);
	result->SetCollider(true);
	result->SetMeshName(_meshName);
	result->SetHealth(30);
	EntityManager::GetInstance()->AddNinjaEntity(result);

	return result;
}