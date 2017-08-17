#pragma once
#include "../GenericEntity.h"
#include "../GroundEntity.h"

#include <vector>
using namespace std;

class Mesh;

class CEnemy3D :
	public GenericEntity
{
protected:
	enum CENEMY3D_TYPE
	{
		NONE = 0,
		TROOP,
		TURRET,
		NINJA,
		TOTAL
	};

	Mesh* modelMesh;

	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 target, up, rotate;
	Vector3 maxBoundary, minBoundary;
	Vector3 destination, finalDestination;
	GroundEntity* m_pTerrain;
	CENEMY3D_TYPE type;

	double m_dSpeed;
	double m_dAcceleration;
	float m_fElapsedTimeBeforeUpdate;
	bool m_bChangeDir;
	bool m_bChangeDestination;

public:
	CEnemy3D(Mesh* _modelMesh);
	virtual ~CEnemy3D();

	void Init(void);
	// Reset this player instance to default
	void Reset(void);
	
	//Reset game
	void ResetGame();

	// Set position
	void SetPos(const Vector3& pos);
	// Set target
	void SetTarget(const Vector3& target);
	// Set Up
	void SetUp(const Vector3& up);
	// Set the boundary for the player info
	void SetBoundary(Vector3 max, Vector3 min);
	// Set the terrain for the player info
	void SetTerrain(GroundEntity* m_pTerrain);
	void SetType(int type);
	void SetDestination(Vector3 destination);

	// Get position
	Vector3 GetPos(void) const;
	// Get target
	Vector3 GetTarget(void) const;
	// Get Up
	Vector3 GetUp(void) const;
	// Get the terrain for the player info
	GroundEntity* GetTerrain(void);
	//Get final destination
	Vector3 GetFinalDestination() { return finalDestination; };

	// Update
	void Update(double dt = 0.0333f);

	// Constrain the position within the borders
	void Constrain(void);
	// Render
	void Render(void);

	void SetMesh(Mesh* mesh);
};

namespace Create
{
	CEnemy3D* Enemy3D(const std::string& _meshName,
						const Vector3& _position,
						const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f),
						const int type = 1);
};