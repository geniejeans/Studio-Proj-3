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
	std::list<EntityBase*>::iterator it, it2, end, it3;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->Update(_dt);
		//Resetting all collision to false
		if ((*it)->GetMeshName() == "testTroop")
			(*it)->SetCollide(false);
	}
	for (it = troopList.begin(); it != troopList.end(); ++it)
	{
		//WIP
		/*for (it3 = troopList.begin(); it3 != troopList.end(); ++it3)
		{
			if ((*it != *it3) && (!(*it)->GetActionDone() && (*it3)->GetActionDone()))
			{
				if (CheckSphereCollision(*it, *it3))
				{
					(*it)->SetBuffer(3);
					(*it)->SetAvoidPos((*it3)->GetPosition());
					(*it)->SetCollide(true);
					break;
				}
			}
		}*/
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
			//If TROOPS are never in any collision after checking through all objects
			if (!(*it)->GetCollide())
			{
				(*it)->SetBuffer(0);
			}
	}

	// Clean up entities that are done
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
		{
			// Move on otherwise
			++it;
		}
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


