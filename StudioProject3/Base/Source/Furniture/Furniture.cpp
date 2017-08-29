#include "Furniture.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"

CFurniture* CFurniture::Instance = 0;

CFurniture::CFurniture()
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

}

CFurniture::CFurniture(Mesh* _modelMesh)
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
	if (meshName == "playerBase")
	{
		modelStack.Rotate(180, 0, 1, 0);
	}
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();

	if (meshName == "enemyBase")
	{
		modelStack.PushMatrix();
		modelStack.Translate(position.x, scale.y + 10, position.z);
		modelStack.Scale(m_iHealth / 5, 1, 1);
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("healthR"));
		modelStack.PopMatrix();
	}
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

	if (_meshName == "enemyBase" || _meshName == "playerBase")
	{
		result->SetHealth(300);
	}
//	EntityManager::GetInstance()->AddEntity(result);
	EntityManager::GetInstance()->AddOther(result);
	return result;
}