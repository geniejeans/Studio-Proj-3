#include "EntityManager.h"
#include "EntityBase.h"
#include "Collider/Collider.h"
#include "GenericEntity.h"
#include "CameraEffects\CameraEffects.h"
#include "MeshBuilder.h"

#include <iostream>
using namespace std;

// Update all entities
void EntityManager::Update(double _dt)
{
	std::list<EntityBase*>::iterator it, it2, it3, it4, it5, end;
	end = entityList.end();
	//Resetting collision for all troops========================
	for (it = troopList.begin(); it != troopList.end(); ++it)
	{
		(*it)->SetCollide(false);
	}
	//Setting conditions for TROOP collisions====================
	for (it = troopList.begin(); it != troopList.end(); ++it)
	{
		//Checking for TURRETS colliding into TROOPS
		for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
		{
			if (CheckSphereCollision(*it, *it2))
			{
				(*it)->SetBuffer(2);
				(*it)->SetAvoidPos((*it2)->GetPosition());
				(*it)->SetCollide(true);
			}
		}

		//If TROOPS are never in any collision after checking through all OBJECTS
		if (!(*it)->GetCollide())
			{
				(*it)->SetBuffer(0);
			}
	}
	//Setting conditions for TURRET collisions====================
	for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
	{
		for (it4 = troopProjectileList.begin(); it4 != troopProjectileList.end(); it4++)
		{
			//This ensures that troops fires at correct turrets. Can take this out once mouse selction is implemented
			if ((*it4)->GetFireDestination() != (*it2)->GetPosition()) 
				continue;

			if (CheckSphereCollision(*it2, *it4))
			{
				(*it2)->SetIsDone(true);
				(*it4)->SetIsDone(true);
			}
		}
	}

	// Turret Projectiles, Collision of Projectiles and Troops.
	for (it = troopList.begin(); it != troopList.end(); ++it)
	{
		for (it5 = turretProjectileList.begin(); it5 != turretProjectileList.end(); it5++)
		{
			// Checking Bullet with Troop
			if (CheckSphereCollision(*it, *it5))
			{
				(*it)->SetIsDone(true);
				(*it5)->SetIsDone(true);
			}
		}
	}

	// 
	for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
	{
		CEnemy3D* turret = dynamic_cast<CEnemy3D*>(*it2);

		Vector3 targetPos;
		turret->m_fElapsedTimeBeforeUpdate += _dt;

		for (it4 = troopList.begin(); it4 != troopList.end(); it4++)
		{
			CEnemy3D* troop = dynamic_cast<CEnemy3D*>(*it4);

			// Making the range of 40 * 40, and ensuring that the closest troops are shoot first.
			if ((troop->GetPos() - turret->GetPos()).LengthSquared() < 40 * 40 && (targetPos.IsZero() || 
				(troop->GetPos() - turret->GetPos()).LengthSquared() < (targetPos - turret->GetPos()).LengthSquared()))
			{
				targetPos = troop->GetPos();
			}
		}
		
		// Ensure that the turret is not shooting immediately and if targetPos is not zero.
		if (turret->m_fElapsedTimeBeforeUpdate > 0.5 && !targetPos.IsZero())
		{
			turret->m_fElapsedTimeBeforeUpdate = 0;
			turret->SetFire(true);
			turret->SetFireDestination(targetPos);

			continue;
		}
		turret->SetFire(false);
	}

	//Cleaning up ENTITIES that are done========================	
	for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
	{
		if ((*it2)->IsDone())
			it2 = turretList.erase(it2);
	}

	for (it4 = troopProjectileList.begin(); it4 != troopProjectileList.end(); ++it4)
	{
		if ((*it4)->IsDone())
			it4 = troopProjectileList.erase(it4);
		//Prevents invalid reading of list
		if (troopProjectileList.size() == 0)
			break;
	}

	// Cleaning up troop
	it = troopList.begin();
	while (it != troopList.end())
	{
		if ((*it)->IsDone())
		{
			// Remove troop when done
			it = troopList.erase(it);
		}
		else
			// Move on otherwise
			++it;
	}

	// Cleaning up turret projectile
	it5 = turretProjectileList.begin();
	while (it5 != turretProjectileList.end())
	{
		if ((*it5)->IsDone())
		{
			// Remove turret projectile when done
			it5 = turretProjectileList.erase(it5);
		}
		else
			// Move on otherwise
			++it5;
	}


	// Delete everything after clean up
	it = entityList.begin();
	while (it != end)
	{
		if ((*it)->IsDone())
		{
			// Delete if done
			delete *it;
			it = entityList.erase(it);
		}
		else
			// Move on otherwise
			++it;
	}

	//Updating ENTITIES============================================
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->Update(_dt);
	}

}
void EntityManager::ResetGame(CPlayerInfo *Player)
{
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->ResetGame();
	}
	Player->ResetGame();
}

// Render all entities
void EntityManager::Render()
{
	// Render all entities
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->Render();
	}
}

// Render the UI entities
void EntityManager::RenderUI()
{
	// Render all entities UI
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->RenderUI();
	}
}

// Add an entity to this EntityManager
void EntityManager::AddEntity(EntityBase* _newEntity)
{
	entityList.push_back(_newEntity);
}

void EntityManager::AddTurretEntity(EntityBase* _newEntity)
{
	turretList.push_back(_newEntity);
}

void EntityManager::AddTroopEntity(EntityBase* _newEntity)
{
	troopList.push_back(_newEntity);
}
void EntityManager::AddTroopProjectileEntity(EntityBase* _newEntity)
{
	troopProjectileList.push_back(_newEntity);
}

void EntityManager::AddTurretProjectileEntity(EntityBase* _newEntity)
{
	turretProjectileList.push_back(_newEntity);
}

// Remove an entity from this EntityManager
bool EntityManager::RemoveEntity(EntityBase* _existingEntity)
{
	// Find the entity's iterator
	std::list<EntityBase*>::iterator findIter = std::find(entityList.begin(), entityList.end(), _existingEntity);

	// Delete the entity if found
	if (findIter != entityList.end())
	{
		delete *findIter;
		findIter = entityList.erase(findIter);
		return true;	
	}
	// Return false if not found
	return false;
}

// Constructor
EntityManager::EntityManager()
{
}

// Destructor
EntityManager::~EntityManager()
{
}

// Check for overlap
bool EntityManager::CheckOverlap(Vector3 thisMinAABB, Vector3 thisMaxAABB, Vector3 thatMinAABB, Vector3 thatMaxAABB)
{	

	return false;
}

// Check if this entity's bounding sphere collided with that entity's bounding sphere 
bool EntityManager::CheckSphereCollision(EntityBase *ThisEntity, EntityBase *ThatEntity)
{
	float distance = sqrt(((ThatEntity->GetPosition().x - ThisEntity->GetPosition().x) * (ThatEntity->GetPosition().x - ThisEntity->GetPosition().x))
		+ ((ThatEntity->GetPosition().z - ThisEntity->GetPosition().z) * (ThatEntity->GetPosition().z - ThisEntity->GetPosition().z)));

	float ObjOneRadius = ThisEntity->GetScale().x + 1 + ThisEntity->GetBuffer();

	float ObjTwoRadius = ThatEntity->GetScale().x + 1 + ThisEntity->GetBuffer();

	float sumOfRadius = ObjOneRadius + ObjTwoRadius;

	if (distance > sumOfRadius)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Check if this entity collided with another entity, but both must have collider
bool EntityManager::CheckAABBCollision(EntityBase *ThisEntity, EntityBase *ThatEntity)
{

	return false;
}

// Check if any Collider is colliding with another Collider
bool EntityManager::CheckForCollision(void)
{

	return false;
}

void EntityManager::CollisionResponse(EntityBase *ThisEntity, EntityBase *ThatEntity)
{

}

void EntityManager::ClearEntityList()
{
	std::list<EntityBase*>::iterator it, it2, it3, end;
	it = entityList.begin();
	end = entityList.end();
	
	entityList.clear();
	turretList.clear();
	troopList.clear();
}

