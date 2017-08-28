#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "SingletonTemplate.h"
#include <list>
#include "Vector3.h"
#include "PlayerInfo\PlayerInfo.h"

class EntityBase;

class EntityManager : public Singleton<EntityManager>
{
	friend Singleton<EntityManager>;
public:
	void Update(double _dt);
	void Render();
	void RenderUI();

	void AddEntity(EntityBase* _newEntity);
	void AddOther(EntityBase* _newEntity);

	void AddTurretEntity(EntityBase* _newEntity);

	void AddTroopEntity(EntityBase* _newEntity);
	void AddNinjaEntity(EntityBase* _newEntity);
	void AddTroopProjectileEntity(EntityBase* _newEntity);
	void AddTurretProjectileEntity(EntityBase* _newEntity);
	// Add Trees
	void AddTreesEntity(EntityBase* _newEntity);
	void AddBombEntity(EntityBase* _newEntity);

	bool RemoveEntity(EntityBase* _existingEntity);
	void ClearEntityList();

	void UpdateAllList(double _dt); //All updates of lists are inside this function for neater codes
	void CleanAllList();//All cleaning of lists are inside this function for neater codes

	std::list<EntityBase*> GetTroopList() { return troopList; };
	float m_fBuffer = 0.0f;

	void GenerateNinja(GroundEntity *groundEntity, double dt);

private:
	EntityManager();
	virtual ~EntityManager();

	// Check for overlap
	bool CheckOverlap(Vector3 thisMinAABB, Vector3 thisMaxAABB, Vector3 thatMinAABB, Vector3 thatMaxAABB);
	// Check if this entity's bounding sphere collided with that entity's bounding sphere 
	bool CheckSphereCollision(EntityBase *ThisEntity, EntityBase *ThatEntity);
	// Check if this entity collided with another entity, but both must have collider
	bool CheckAABBCollision(EntityBase *ThisEntity, EntityBase *ThatEntity);
	// Check if any Collider is colliding with another Collider
	bool CheckForCollision(void);

	void CollisionResponse(EntityBase *ThisEntity, EntityBase *ThatEntity);


	void ResetGame(CPlayerInfo *Player);

	std::list<EntityBase*> entityList;
	std::list<EntityBase*> turretList;
	std::list<EntityBase*> troopList;
	std::list<EntityBase*> ninjaList;
	std::list<EntityBase*> troopProjectileList;
	std::list<EntityBase*> turretProjectileList;
	std::list<EntityBase*> bombList;
	std::list<EntityBase*> otherList; //This list contains base
	std::list<EntityBase*> TreesList; //This list contains tree
};

#endif // ENTITY_MANAGER_H