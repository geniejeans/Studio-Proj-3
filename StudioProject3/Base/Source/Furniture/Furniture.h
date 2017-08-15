#ifndef FURNITURE_H
#define FURNITURE_H
#include "Collider\Collider.h"
#include "../EntityManager.h"
#include "../GenericEntity.h"
#include "../GroundEntity.h"
using namespace std;

class CFurniture : public GenericEntity
{
public:
	CFurniture(Mesh* _modelMesh);
	~CFurniture();

	 void Render(void);
protected:

	Mesh* modelMesh;

	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 target, up;
	Vector3 maxBoundary, minBoundary;
	GroundEntity* m_pTerrain;
};
namespace Create
{
	CFurniture* Furniture3D(const std::string& _meshName,
		const Vector3& _position,
		const Vector3& _scale = Vector3(2.0f, 2.0f, 2.0f));
}
#endif // ! FURNITURE_H
