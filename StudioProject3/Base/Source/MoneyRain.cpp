#include "MoneyRain.h"
#include "GLFW\glfw3.h"

MoneyRain::MoneyRain(Mesh * _modelMesh)
{
	modelmesh = _modelMesh;
}

MoneyRain::~MoneyRain()
{
}

void MoneyRain::Render()
{
	glEnable(GL_BLEND);
	// Activate the Blend Function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelmesh);
	modelStack.PopMatrix();

	glDisable(GL_BLEND);
}

MoneyRain * Create::Money(const std::string & _meshName)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	MoneyRain* result = new MoneyRain(modelMesh);
	EntityManager::GetInstance()->AddEntity(result);
	return result;

}
