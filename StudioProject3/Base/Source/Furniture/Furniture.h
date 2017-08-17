#ifndef FURNITURE_H
#define FURNITURE_H

#include "Collider\Collider.h"
#include "../EntityManager.h"
#include "../GenericEntity.h"
#include "../GroundEntity.h"
#include "../ReadFile/FileManager.h"

#include <vector>
using namespace std;

class CFurniture : public GenericEntity
{
	static CFurniture* Instance;
public:
	CFurniture();
	CFurniture(Mesh* _modelMesh);
	~CFurniture();

	 void Render(void);

	 //get static pointer
	 static CFurniture* GetInstance()
	 {
		 if (!Instance) //no instance is found
			 Instance = new CFurniture(); //create new instance

		 return Instance;
	 }

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
		const Vector3& _scale);
}
#endif // ! FURNITURE_H
