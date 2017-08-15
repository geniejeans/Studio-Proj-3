#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include "Vector3.h"
#include <string>
using std::string;

class Mesh;

class EntityBase
{
public:
	EntityBase();
	virtual ~EntityBase();

	virtual void Update(double _dt);
	virtual void Render();
	virtual void RenderUI();

	inline void SetPosition(const Vector3& _value){ position = _value; };
	inline Vector3 GetPosition(){ return position; };

	inline void SetScale(const Vector3& _value){ scale = _value; };
	inline Vector3 GetScale(){ return scale; };

	inline void SetMeshName(const string& _value) { meshName = _value; };
	inline string GetMeshName() { return meshName; };

	bool IsDone();
	void SetIsDone(const bool _value);

	// Check if this entity has a collider class parent
	virtual bool HasCollider(void) const;
	// Set the flag to indicate if this entity has a collider class parent
	virtual void SetCollider(const bool _value);
	//Set new mesh
	virtual void SetMesh(Mesh* mesh);

	//Set collision with player
	virtual void SetCollidePlayer(const bool _value) { m_bCollidePlayer = _value; };
	virtual bool GetCollidePlayer() { return m_bCollidePlayer; };

	//Reset 
	virtual void ResetGame();

protected:
	Vector3 position;
	Vector3 scale;
	string meshName;

	bool isDone;
	bool m_bCollider;
	bool m_bCollidePlayer;

	Mesh* modelMesh;
};

#endif // ENTITY_BASE_H