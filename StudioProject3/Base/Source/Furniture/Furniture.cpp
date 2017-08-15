#include "Furniture.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"


CFurniture::CFurniture(Mesh* _modelMesh)
	: GenericEntity(NULL)
	, defaultPosition(Vector3(0.0f, 0.0f, 0.0f))
	, defaultTarget(Vector3(0.0f, 0.0f, 0.0f))
	, defaultUp(Vector3(0.0f, 0.0f, 0.0f))
	, target(Vector3(0.0f, 0.0f, 0.0f))
	, up(Vector3(0.0f, 0.0f, 0.0f))
	, maxBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, minBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, m_pTerrain(NULL)
{
	this->modelMesh = _modelMesh;
}


CFurniture::~CFurniture()
{
}

void CFurniture::Render(void)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();
}

CFurniture* Create::Furniture3D(const std::string& _meshName,
	const Vector3& _position,
	const Vector3& _scale)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	CFurniture* result = new CFurniture(modelMesh);
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

	EntityManager::GetInstance()->AddEntity(result);
	return result;
}