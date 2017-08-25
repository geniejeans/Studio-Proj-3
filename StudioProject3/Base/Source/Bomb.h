#pragma once
//#include "../GenericEntity.h"
//#include "../GroundEntity.h"
#include "SingletonTemplate.h"
#include "GenericEntity.h"
#include "GroundEntity.h"

#include <vector>
using std::vector;

class Bomb : public GenericEntity, public Singleton<Bomb>
{
	friend Singleton<Bomb>;
public:
	Bomb();
	Bomb(Mesh* _modelMesh);
	~Bomb();
	//void init();

	// Render the Bomb objects
	void Render(void);
	// Update the Bomb objects
	void Update(double dt);


	static bool b_LMBtrue;

	bool GetBombActive();
	static void SetBombActive(bool IsRendered);

protected:
	Mesh* modelMesh;

	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 target, up;
	Vector3 maxBoundary, minBoundary;
	GroundEntity* m_pTerrain;


private:
	// Max Size of Bomb
	Vector3 MaxScale;
	// Size of scale 
	Vector3 m_Scale;
	// Rate of scale
	Vector3 m_Rate;

	// Bool to check if able to spawn
	bool m_bSpawn;
	// Interval to spawn Bomb
	double m_dSpawnTime;
	// Time for each Interval
	static double m_dRate;
};

namespace Create
{
	Bomb* Bomb3D(const std::string& _meshName,
		const Vector3& _position,
		const Vector3& _scale);
}
