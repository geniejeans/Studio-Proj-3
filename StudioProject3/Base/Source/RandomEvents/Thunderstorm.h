#ifndef THUNDER_STORM_H	
#define THUNDER_STORM_H

#include <string>
#include "Vector3.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "../EntityManager.h"
#include "EntityBase.h"

class Mesh;

class Thunderstorm : public EntityBase
{
	Vector3 position;
	Vector3 scale;
	Vector3 vel;

	Mesh* modelmesh;

public:
	Thunderstorm(Mesh* _modelMesh);
	virtual ~Thunderstorm();

	virtual void Update(double dt) { }
	virtual void Render();

	// Position
	void SetPosition(Vector3& _value) { position = _value; }
	Vector3 GetPosition() { return position; }

	// Scale
	void SetScale(Vector3& _value) { scale = _value; }
	Vector3 GetScale() { return scale; }

	// Vel
	void SetVel(Vector3& _value) { vel = _value; }
	Vector3 GetVel() { return vel; }
};

namespace Create
{
	Thunderstorm* Storm(const std::string& _meshName);
};

#endif