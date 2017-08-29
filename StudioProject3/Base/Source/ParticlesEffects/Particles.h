#pragma once
#include "SingletonTemplate.h"
#include "../GenericEntity.h"

#include "Vector3.h"

class Mesh;
class Particles : public GenericEntity
{
	Mesh* modelMesh;
	Vector3 m_velocity, m_Gravity;

	// Boolean to indicate the spawning of particles
	static bool m_bIsSpawn;

	// The speed of the particles
	float m_speed;

public:
	Particles() {};
	Particles(Mesh* modelMesh);
	~Particles();

	void Init(void);
	void Update(double dt);
	void Render(void);
	
	// Postion of particle
	//void SetPos(Vector3& pos);
	//Vector3 GetPos();

	// Velocity of particle
	void SetVel(Vector3& vel);
	Vector3 GetVel();

	// Boolean 
	void SetIsSpawn(bool m_bSpawn);
	bool GetIsSpawn();



	// Time of particles 
	double m_dInterval;
};

namespace Create
{
	Particles* Partcle(const string& _meshName,
		const Vector3& _pos,
		const Vector3& _scale);
}