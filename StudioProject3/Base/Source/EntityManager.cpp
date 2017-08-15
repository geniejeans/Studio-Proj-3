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
	bool playerCollide = false;
	std::list<EntityBase*>::iterator it, it2, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->Update(_dt);
	}

	for (it = entityList.begin(); it != end; ++it)
	{
		if ((*it)->HasCollider())
		{
			//Checking for PLAYER colliding into objects 
			if (CheckPlayerSphereCollision(CPlayerInfo::GetInstance(), *it))
			{
				CollisionPlayerResponse(CPlayerInfo::GetInstance(), *it);
				playerCollide = true;
			}
			else if (!playerCollide)
			{
				CPlayerInfo::GetInstance()->SetCollision(false);
				(*it)->SetCollidePlayer(false);
			}
			//Checking for OBJECTS colliding into objects
			for (it2 = it; it2 != end; ++it2)
			{
				if ((*it2)->HasCollider())
				{
				}
			}
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

	double distance = sqrt(((ThatEntity->GetPosition().x - ThisEntity->GetPosition().x) * (ThatEntity->GetPosition().x - ThisEntity->GetPosition().x))
		+ ((ThatEntity->GetPosition().y - ThisEntity->GetPosition().y) * (ThatEntity->GetPosition().y - ThisEntity->GetPosition().y))
		+ ((ThatEntity->GetPosition().z - ThisEntity->GetPosition().z) * (ThatEntity->GetPosition().z - ThisEntity->GetPosition().z)));

	double ObjOneRadius = ThisEntity->GetScale().x;

	double ObjTwoRadius = ThatEntity->GetScale().x;

	double sumOfRadius = ObjOneRadius + ObjTwoRadius;

	if (distance > sumOfRadius)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool EntityManager::CheckPlayerSphereCollision(CPlayerInfo *Player, EntityBase *ThisEntity)
{
	double distance = sqrt(((ThisEntity->GetPosition().x - Player->GetPos().x) * (ThisEntity->GetPosition().x - Player->GetPos().x))

		+ ((ThisEntity->GetPosition().z - Player->GetPos().z) * (ThisEntity->GetPosition().z - Player->GetPos().z)));

	double PlayerRadius = 5;

	double ObjOneRadius = ThisEntity->GetScale().x;

	double sumOfRadius = PlayerRadius + ObjOneRadius;

	if (distance > sumOfRadius + 5)
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

void EntityManager::CollisionPlayerResponse(CPlayerInfo *Player, EntityBase *ThisEntity)
{

	Player->SetCollision(true);
}


