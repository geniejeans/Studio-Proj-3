#pragma once
#include "../GenericEntity.h"
#include "../GroundEntity.h"
#include "SingletonTemplate.h"

#include <vector>
using std::vector;

class Trees : public GenericEntity, public Singleton<Trees>
{
	friend Singleton<Trees>;
public:
	Trees();
	Trees(Mesh* _modelMesh);
	~Trees();
	//void init();

	// Render the tree objects
	void Render(void);
	// Update the tree objects
	void Update(double dt);

	// Set the Scale of trees
	void SetScaleSize(Vector3 size);
	// Get Scale size
	Vector3 GetScaleSize();

	// Set Count of Trees
	void SetCountOfTrees(int count);
	// Get Count of Trees
	int GetCountOfTrees();

	// Set Max
	void SetMaxCount(int max);
	// Get Max
	int GetMaxCount();

	// Set Spawn Rate
	void SetSpawnRate(double rate);
	// Get Spawn Rate
	double GetSpawnRate();

protected:
	Mesh* modelMesh;

	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 target, up;
	Vector3 maxBoundary, minBoundary;
	GroundEntity* m_pTerrain;

private:
	// Max Size of trees
	Vector3 MaxScale;
	// Size of scale 
	Vector3 m_Scale;
	// Rate of scale
	Vector3 m_Rate;

	// Bool to check if able to spawn
	bool m_bSpawn;
	// Limit the number of trees on scene
	static int m_iCountTree;
	// Max number of Trees to be spawn 
	static int m_iMaxCountOfTrees;

	// Interval to spawn trees
	double m_dSpawnTime;
	// Time for each Interval
	static double m_dRate;
};

namespace Create
{
	Trees* Trees3D(const std::string& _meshName,
		const Vector3& _position,
		const Vector3& _scale);
}
