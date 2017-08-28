#include "Trees.h"

#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"

int Trees::m_iCountTree = 0;
int Trees::m_iMaxCountOfTrees = 0;
double Trees::m_dRate = 0;

Trees::Trees(Mesh* _modelMesh)
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
	, m_bSpawn(false)
{
	this->modelMesh = _modelMesh;
}

Trees::~Trees()
{
}

void Trees::Render(void)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(m_Scale.x, m_Scale.y, m_Scale.z);
	modelStack.PushMatrix();
	modelStack.Translate(0, scale.y + 10, 0);
	modelStack.Scale(m_iHealth / 5, 0.3, 1);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("healthR"));
	modelStack.PopMatrix();
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();
}

// This function will be called in EntityManager to update the trees
void Trees::Update(double dt)
{
	m_dSpawnTime -= dt;
	if (m_dSpawnTime > 0.0)
	{
		m_bSpawn = false;
		if (m_Scale < Vector3(5, 5, 5))
		{
			m_Scale += Vector3(1, 1, 1) * dt;
		}
	}
	else if (m_dSpawnTime < 0.0)
	{
		if (!m_bSpawn && m_iCountTree < m_iMaxCountOfTrees)
		{
			m_iCountTree++;
			m_bSpawn = true;
			Create::Trees3D("tree",
				Vector3(Math::RandFloatMinMax(-300, 300)
					,10,
					Math::RandFloatMinMax(-300, 300)),
				Trees::GetInstance()->GetScale());
		}
		m_dSpawnTime = m_dRate;
	}
}

void Trees::SetScaleSize(Vector3 size)
{
	this->m_Scale = size;
}

Vector3 Trees::GetScaleSize()
{
	return m_Scale;
}

void Trees::SetCountOfTrees(int count)
{
	m_iCountTree = count;
}

int Trees::GetCountOfTrees()
{
	return m_iCountTree;
}

void Trees::SetMaxCount(int max)
{
	this->m_iMaxCountOfTrees = max;
}

int Trees::GetMaxCount()
{
	return m_iMaxCountOfTrees;
}

void Trees::SetSpawnRate(double rate)
{
	m_dRate = rate;
}

double Trees::GetSpawnRate()
{
	return m_dRate;
}

Trees* Create::Trees3D(const std::string& _meshName,
	const Vector3& _position,
	const Vector3& _scale)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	Trees* result = new Trees(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);

	// scale keep increasing
	result->SetScaleSize(_scale);

	result->SetCollider(true);
	result->SetMeshName(_meshName);

	// Set collision
	result->SetAABB(Vector3(_position.x + result->GetScale().x,
		_position.y + result->GetScale().y,
		_position.z + result->GetScale().z),
		Vector3(-_position.x - result->GetScale().x,
			_position.y - result->GetScale().y,
			_position.z - result->GetScale().z));

	// Set Health of tree
	if (_meshName == "tree")
	{
		result->SetHealth(30);
	}

	EntityManager::GetInstance()->AddTreesEntity(result);
	return result;
}