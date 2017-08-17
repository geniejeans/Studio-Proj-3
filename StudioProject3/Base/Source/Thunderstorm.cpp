#include "Thunderstorm.h"
#include "GLFW\glfw3.h"

Thunderstorm::Thunderstorm(Mesh * _modelMesh)
{
	modelmesh = _modelMesh;
}

Thunderstorm::~Thunderstorm()
{
}

void Thunderstorm::Render()
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

Thunderstorm * Create::Storm(const std::string & _meshName)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	Thunderstorm* result = new Thunderstorm(modelMesh);
	EntityManager::GetInstance()->AddEntity(result);
	return result;

}
