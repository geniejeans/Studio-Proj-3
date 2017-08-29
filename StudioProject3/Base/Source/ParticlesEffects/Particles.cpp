#include "Particles.h"

#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "Renderhelper.h"
#include "../EntityManager.h"

#include <iostream>

bool Particles::m_bIsSpawn = false;

Particles::Particles(Mesh* modelMesh)
	: m_velocity(0.f, 0.f, 0.f)
	, m_Gravity(0.f,0.f,0.f)
	, m_speed(0)
	, m_dInterval(0.0)
		
{
	this->modelMesh = modelMesh;
}

Particles::~Particles()
{
}

void Particles::Init(void)
{
	m_velocity.Set(0.f, 10.f, 0.f);
	m_Gravity.Set(0.f, -2.8f, 0.f);
	m_dInterval = 0.0;

	m_speed = 10.f;
}

void Particles::Update(double dt)
{
	// Spawning of particles when true
	if (m_bIsSpawn)
	{
		m_velocity += m_Gravity * (float)dt * (float)m_speed;
		position += m_velocity * (float)dt * (float)m_speed;
		m_dInterval += dt;
		if (m_dInterval > 1.f)
		{
			isDone = true;
			m_bIsSpawn = false;
			m_dInterval = 0.0;
		}
	}
	else
	{
		m_dInterval = 0.0;
	}

}

void Particles::Render(void)
{
	if (m_bIsSpawn)
	{
		MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, position.z);
		modelStack.Scale(scale.x, scale.y, scale.z);
		RenderHelper::RenderMesh(modelMesh);
		modelStack.PopMatrix();
	}
}

void Particles::SetVel(Vector3 & vel)
{
	m_velocity = vel;
}

Vector3 Particles::GetVel()
{
	return m_velocity;
}

void Particles::SetIsSpawn(bool m_bSpawn)
{
	if(!m_bIsSpawn)
		this->m_bIsSpawn = m_bSpawn;
}

bool Particles::GetIsSpawn()
{
	return m_bIsSpawn;
}

Particles * Create::Partcle(const string & _meshName, const Vector3 & _pos, const Vector3 & _scale)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	Particles* result = new Particles(modelMesh);
	result->SetPosition(_pos);
	result->SetScale(_scale);
	//result->SetVel(m_velocity);
	result->SetMeshName(_meshName);

	EntityManager::GetInstance()->AddParticleEntity(result);
	return result;
}