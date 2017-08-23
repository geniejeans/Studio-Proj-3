#pragma once
#include <string>
#include "Vector3.h"

#include "Mesh.h"
#include "EntityBase.h"

class Mesh;
class RandomEvents
{
public:
	RandomEvents() {};
	RandomEvents(Mesh* modelMesh) {};
	~RandomEvents() {};

	// Initialise this class instance
	virtual void Init(void) = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;

	// Position
	virtual void SetPos(Vector3& position) = 0;
	virtual Vector3 GetPos() = 0;

	// Scale
	virtual void setScale(Vector3& scale) = 0;
	virtual Vector3 GetScale() = 0;

	// Vel
	virtual void SetVel(Vector3& velocity) = 0;
	virtual Vector3 GetVel() = 0;
};