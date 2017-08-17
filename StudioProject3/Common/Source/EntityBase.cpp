#include "EntityBase.h"
#include "MeshBuilder.h"

EntityBase::EntityBase() 
	: position(0.0f, 0.0f, 0.0f)
	, scale(1.0f, 1.0f, 1.0f)
	, objAvoidPos(0.0f,0.0f,0.0f)
	, meshName ("")
	, m_fBuffer(0.0f)
	, isDone(false)
	, m_bCollider(false)
	, m_bCollide(false)
	,m_bActionDone(false)
{
}

EntityBase::~EntityBase()
{
}

void EntityBase::Update(double _dt)
{
}

void EntityBase::Render()
{
}

void EntityBase::RenderUI()
{
}

void EntityBase::ResetGame()
{

}

bool EntityBase::IsDone()
{
	return isDone;
}

void EntityBase::SetIsDone(bool _value)
{
	isDone = _value;
}

// Check if this entity has a collider class parent
bool EntityBase::HasCollider(void) const
{
	return m_bCollider;
}

// Set the flag to indicate if this entity has a collider class parent
void EntityBase::SetCollider(const bool _value)
{
	m_bCollider = _value;
}

void EntityBase::SetMesh(Mesh* mesh)
{
	modelMesh = mesh;
}