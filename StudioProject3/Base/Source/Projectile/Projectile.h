#pragma once
#include "EntityBase.h"
#include "Vector3.h"
#include "Collider/Collider.h"

class Mesh;
class CEnemy3D;
class Turret;
class GenericEntity;

class CProjectile : public EntityBase, public CCollider
{
public:
	CProjectile(void);
	CProjectile(Mesh* _modelMesh);
	~CProjectile(void);

	// Activate the projectile. true == active, false == inactive
	void SetStatus(const bool m_bStatus);
	// get status of the projectile. true == active, false == inactive
	bool GetStatus(void) const;
	// Set the position and direction of the projectile
	void Set(	Vector3 theNewPosition, 
				Vector3 theNewDirection, 
				const float m_fLifetime, 
				const float m_fSpeed);
	void SetDirection(Vector3 theNewDirection);
	// Get the direction of the projectile
	Vector3 GetDirection(void);
	// Set the lifetime of the projectile
	void SetLifetime(const float m_fLifetime);
	// Get the lifetime of the projectile
	float GetLifetime(void) const;
	// Set the speed of the projectile
	void SetSpeed(const float m_fSpeed);
	// Get the speed of the projectile
	float GetSpeed(void) const;
	// Set the source of the projectile
	void SetSource(GenericEntity* _source);
	// Get the source of the projectile
	GenericEntity* GetSource(void) const;

	void SetFireDestination(Vector3 destination) { fireDestination = destination; };
	Vector3 GetFireDestination() { return fireDestination; };
	// Update the status of this projectile
	virtual void Update(double dt = 0.0333f);
	// Render this projectile
	virtual void Render(void);
protected:
	enum PROJECTILE_TYPE
	{
		NONE = 0,
		TROOP,
		TURRET,

		NUM_PROJECTILE
	};
	PROJECTILE_TYPE projectile;

	// The model mesh for this projectile
	Mesh* modelMesh;
	// Boolean flag to indicate if this projectile is active. If not active, then do not compute/update
	bool m_bStatus;
	// Remaining lifetime in seconds
	float m_fLifetime;
	// Speed of this projectile in unit / sec
	float m_fSpeed;
	// The direction of the projectile
	Vector3 theDirection;
	// The character which fired this projectile
	GenericEntity* theSource;

public:
	void SetProjType(int type);
	
};

namespace Create
{
	CProjectile* Projectile(const std::string& _meshName, 
							const Vector3& _position, 
							const Vector3& _direction, 
							const float m_fLifetime, 
							const float m_fSpeed,
							const int m_iType,
		                    GenericEntity* _source=NULL);
};

