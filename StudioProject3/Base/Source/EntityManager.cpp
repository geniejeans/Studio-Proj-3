#include "EntityManager.h"
#include "EntityBase.h"
#include "Collider/Collider.h"
#include "GenericEntity.h"
#include "MeshBuilder.h"
#include "MoneyManager\Money.h"
#include "Trees\Trees.h"
#include "Enemy\RadarScan.h"
#include "Bomb.h"
#include "Enemy\Troop3D.h"
#include "Enemy\Turrets\Turrets.h"
#include "Projectile\Projectile.h"
#include "Enemy\Shield.h"
#include "Enemy\Ninja3D.h"

#include <iostream>
using namespace std;
std::list<EntityBase*>::iterator it, it2, it3, it4, it5, it6, it7, it_T, it_T2, it8, it9, it10;

// Update all entities
void EntityManager::Update(double _dt)
{
	// ====================== Conditions for Troops Collision ====================== //
	for (it = troopList.begin(); it != troopList.end(); ++it)
	{
		//Resetting collision for all troops
		(*it)->SetCollide(false); 

		// Turrets - Troops Collision
		for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
		{
			if (CheckSphereCollision(*it, *it2))
			{
				(*it)->SetBuffer(4);
				(*it)->SetAvoidPos((*it2)->GetPosition());
				(*it)->SetCollide(true);
			}
		}

		// Others - Troops Collision
		for (it5 = otherList.begin(); it5 != otherList.end(); ++it5)
		{
			if (CheckSphereCollision(*it, *it5))
			{
				(*it)->SetBuffer(2);
				(*it)->SetAvoidPos((*it5)->GetPosition());
				(*it)->SetCollide(true);
			}
		}

		// Trees - Troops Collision
		for (it_T = TreesList.begin(); it_T != TreesList.end(); ++it_T)
		{
			if (CheckSphereCollision(*it, *it_T))
			{
				(*it)->SetBuffer(2);
				(*it)->SetAvoidPos((*it_T)->GetPosition());
				(*it)->SetCollide(true);
			}
		}

		// No Collision after checking ALL available objects
		if (!(*it)->GetCollide())
		{
			(*it)->SetBuffer(0);
		}
	}

	// ====================== Conditions for Ninja Collision ====================== //
	for (it7 = ninjaList.begin(); it7 != ninjaList.end(); ++it7)
	{
		//Resetting collision for all troops
		(*it7)->SetCollide(false); 
								  
		// Turrets - Ninja
		for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
		{
			if (CheckSphereCollision(*it7, *it2))
			{
				(*it7)->SetBuffer(4);
				(*it7)->SetAvoidPos((*it2)->GetPosition());
				(*it7)->SetCollide(true);
			}
		}

		// Others - Ninja
		for (it5 = otherList.begin(); it5 != otherList.end(); ++it5)
		{
			if (CheckSphereCollision(*it7, *it5))
			{
				(*it7)->SetBuffer(2);
				(*it7)->SetAvoidPos((*it5)->GetPosition());
				(*it7)->SetCollide(true);
			}
		}

		// Trees - Ninja
		for (it_T = TreesList.begin(); it_T != TreesList.end(); ++it_T)
		{
			if (CheckSphereCollision(*it7, *it_T))
			{
				(*it7)->SetBuffer(2);
				(*it7)->SetAvoidPos((*it_T)->GetPosition());
				(*it7)->SetCollide(true);
			}
		}

		// Checking for BOMB colliding into NINJA Esdurr
		for (it8 = bombList.begin(); it8 != bombList.end(); ++it8)
		{
			if (CheckSphereCollision(*it7, *it8))
			{
				if (Bomb::GetInstance()->GetBombActive())
				{
					(*it7)->SetBuffer(2);
					Money::GetInstance()->SetActiveDestroyed(true); // Ninja will +10p when destroyed by Bomb
					Money::GetInstance()->SetIncreaseMoney(10);
					(*it7)->SetIsDone(true);
				}
			}
		}

		// No Collision after checking ALL available objects
		if (!(*it7)->GetCollide())
		{
			(*it7)->SetBuffer(0);
		}

		// Troops Projectile - Ninja
		for (it4 = troopProjectileList.begin(); it4 != troopProjectileList.end(); it4++)
		{
			/*if ((*it4)->GetFireDestination() != (*it6)->GetPosition())  //Leave it in if FPS drops
			continue;*/
			CProjectile* projectile = dynamic_cast<CProjectile*>(*it4);
			if (CheckSphereCollision(*it7, *it4))
			{
				(*it7)->SetHealth((*it7)->GetHealth() - projectile->GetDamage());
				(*it4)->SetIsDone(true);
				if ((*it7)->GetHealth() <= 0)
				{
					Money::GetInstance()->SetActiveDestroyed(true); //Get 10 points for each ninja destroyed by troops
					Money::GetInstance()->SetIncreaseMoney(10);
					(*it7)->SetIsDone(true);
				}
			}
		}
	}

	// ====================== Conditions for Others Collision ====================== //
	for (it6 = otherList.begin(); it6 != otherList.end(); ++it6)
	{
		// Troops Projectile - Others
		for (it4 = troopProjectileList.begin(); it4 != troopProjectileList.end(); it4++)
		{
			/*if ((*it4)->GetFireDestination() != (*it6)->GetPosition())  //Leave it in if FPS drops
				continue;*/
			CProjectile* projectile = dynamic_cast<CProjectile*>(*it4);
			if (CheckSphereCollision(*it6, *it4))
			{
				(*it6)->SetHealth((*it6)->GetHealth() - projectile->GetDamage());
				(*it4)->SetIsDone(true);
				if ((*it6)->GetHealth() <= 0)
				{
					(*it6)->SetIsDone(true);
				}
			}
		}
	}

	// ====================== Conditions for Trees Collision ====================== //
	for (it_T = TreesList.begin(); it_T != TreesList.end(); ++it_T)
	{
		// Trees - Troops Projectile
		for (it4 = troopProjectileList.begin(); it4 != troopProjectileList.end(); it4++)
		{
			if (CheckSphereCollision(*it_T, *it4))
			{
				CProjectile* projectile = dynamic_cast<CProjectile*>(*it4);
				// Health of trees
				(*it_T)->SetHealth((*it_T)->GetHealth() - projectile->GetDamage());
				(*it4)->SetIsDone(true);
				if ((*it_T)->GetHealth() <= 0)
				{
					srand(time(NULL));
					Money::GetInstance()->SetActiveDestroyed(true);
					Money::GetInstance()->SetIncreaseMoney(Math::RandIntMinMax(15, 20)); // +15p when Trees get destroyed by Troops
					Trees::GetInstance()->SetCountOfTrees(Trees::GetInstance()->GetCountOfTrees() - 1);
					(*it_T)->SetIsDone(true);
				}

			//	cout << (*it_T)->GetHealth() << endl;
			}
		}

		// Trees - Others
		for (it6 = otherList.begin(); it6 != otherList.end(); ++it6)
		{
			if (CheckSphereCollision(*it_T, *it6))
			{
				Trees::GetInstance()->SetCountOfTrees(Trees::GetInstance()->GetCountOfTrees() - 1);
				(*it_T)->SetIsDone(true);
			}
		}

		// Trees - Turrets
		for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
		{
			if (CheckSphereCollision(*it_T, *it2))
			{
				Trees::GetInstance()->SetCountOfTrees(Trees::GetInstance()->GetCountOfTrees() - 1);
				(*it_T)->SetIsDone(true);
			}
		}

		// Trees - Bombs
		for (it8 = bombList.begin(); it8 != bombList.end(); ++it8)
		{
			if (CheckSphereCollision(*it_T, *it8))
			{
				if (Bomb::GetInstance()->GetBombActive())
				{
					Trees::GetInstance()->SetCountOfTrees(Trees::GetInstance()->GetCountOfTrees() - 1);
					Money::GetInstance()->SetActiveDestroyed(true);
					Money::GetInstance()->SetIncreaseMoney(Math::RandIntMinMax(15, 20));
					(*it_T)->SetBuffer(2);
					(*it_T)->SetIsDone(true);
				}
			}
		}
	}

	// ====================== Setting Troops' actions / hit ====================== //
	for (it = troopList.begin(); it != troopList.end(); ++it)
	{
		CTroop3D* troop = dynamic_cast<CTroop3D*>(*it);
	
		Vector3 targetPos;
		troop->m_fElapsedTimeBeforeUpdate += _dt;

		if ((*it)->GetActionDone())
		{
			// Others - Troops
			for (it6 = otherList.begin(); it6 != otherList.end(); it6++)
			{
				if (!(*it6)->IsDone() && (*it6)->GetMeshName() =="enemyBase")
				{
					if (((*it6)->GetPosition() - troop->GetPos()).LengthSquared() < troop->GetRange() && (targetPos.IsZero() ||
						((*it6)->GetPosition() - troop->GetPos()).LengthSquared() < (targetPos - troop->GetPos()).LengthSquared()))
					{
						targetPos = (*it6)->GetPosition();
					}
				}
				
			}

			// Trees - Troops
			for (it_T = TreesList.begin(); it_T != TreesList.end(); it_T++)
			{
				if (!(*it_T)->IsDone())
				{
					if (((*it_T)->GetPosition() - troop->GetPos()).LengthSquared() < troop->GetRange() && (targetPos.IsZero() ||
						((*it_T)->GetPosition() - troop->GetPos()).LengthSquared() < (targetPos - troop->GetPos()).LengthSquared()))
					{
						// Set to shoot at object
						targetPos = (*it_T)->GetPosition();
					}
				}
				
			}

			// Turret - Troops
			for (it2 = turretList.begin(); it2 != turretList.end(); it2++)
			{
				if (((*it2)->GetPosition() - troop->GetPos()).LengthSquared() < troop->GetRange() && (targetPos.IsZero() ||
					((*it2)->GetPosition() - troop->GetPos()).LengthSquared() < (targetPos - troop->GetPos()).LengthSquared()))
				{
					targetPos = (*it2)->GetPosition();
				}
			}

			// Ninja - Troops
			for (it7 = ninjaList.begin(); it7 != ninjaList.end(); it7++)
			{
				CNinja3D* ninja = dynamic_cast<CNinja3D*>(*it7);
				if (!ninja->IsDone() && (RadarScan::GetInstance()->GetRPressed() || ninja->m_bRealRendered))
				{
					if (((ninja)->GetPosition() - troop->GetPos()).LengthSquared() < troop->GetRange() && ((ninja)->GetPosition() != troop->GetPos()) &&
						(targetPos.IsZero() || ((ninja)->GetPosition() - troop->GetPos()).LengthSquared() < (targetPos - troop->GetPos()).LengthSquared()))
					{
						// Set to shoot at object
						targetPos = (ninja)->GetPosition();
					}
				}	
			}
		}

		//TROOPS getting hit by TURRET projectiles
		for (it5 = turretProjectileList.begin(); it5 != turretProjectileList.end(); it5++)
		{
			// Checking Bullet with Troop
			if (CheckSphereCollision(*it, *it5))
			{
				CProjectile* projectile = dynamic_cast<CProjectile*>(*it5);
				if (!Shield::GetInstance()->GetShieldActive())
				{
					(*it)->SetHealth((*it)->GetHealth() - projectile->GetDamage());
				}
				(*it5)->SetIsDone(true);
				if ((*it)->GetHealth() <= 0)
				{
					(*it)->SetIsDone(true);
				}
			}
		}

		//Troop shooting's actions
		if (troop->m_fElapsedTimeBeforeUpdate > 0.5 && !targetPos.IsZero())
		{
			troop->m_fElapsedTimeBeforeUpdate = 0;
			troop->SetFire(true);
			troop->SetFireDestination(targetPos);

			continue;
		}
		troop->SetFire(false);
	}

	// ====================== Setting Turret' actions / hit ====================== //
	for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
	{
		Turret* turret = dynamic_cast<Turret*>(*it2);

		Vector3 targetPos;
		turret->m_dCoolDown += _dt;
		int range;

		//TURRET shooting at TROOP
		for (it = troopList.begin(); it != troopList.end(); it++)
		{
			if (!(*it)->IsDone())
			{
				CTroop3D* troop = dynamic_cast<CTroop3D*>(*it);

				if (turret->GetType() == 1 || turret->GetType() == 2)
				{
					// Making the range of 40 * 40, and ensuring that the closest troops are shoot first.
					if ((troop->GetPos() - turret->GetPos()).LengthSquared() < 40 * 40 && (targetPos.IsZero() ||
						(troop->GetPos() - turret->GetPos()).LengthSquared() < (targetPos - turret->GetPos()).LengthSquared()))
					{
						targetPos = troop->GetPos();
						break;
					}
				}
				else if(turret->GetType() == 3)
				{
					// Making the range of 40 * 40, and ensuring that the closest troops are shoot first.
					if ((troop->GetPos() - turret->GetPos()).LengthSquared() < 140 * 140 && (targetPos.IsZero() ||
						(troop->GetPos() - turret->GetPos()).LengthSquared() < (targetPos - turret->GetPos()).LengthSquared()))
					{
						targetPos = troop->GetPos();
						break;
					}
				}
			}
		
		}

		//TURRET getting hit by TROOP projectiles
		for (it4 = troopProjectileList.begin(); it4 != troopProjectileList.end(); it4++)
		{
			if (!(*it4)->IsDone())
			{
				(*it4)->SetBuffer(-4);
				if (CheckSphereCollision(*it4, *it2))
				{
					CProjectile* projectile = dynamic_cast<CProjectile*>(*it4);
					(*it2)->SetHealth((*it2)->GetHealth() - projectile->GetDamage());
					(*it4)->SetIsDone(true);
					if ((*it2)->GetHealth() <= 0)
					{
						(*it2)->SetIsDone(true);
						Money::GetInstance()->SetActiveDestroyed(true);
						Money::GetInstance()->SetIncreaseMoney(Math::RandIntMinMax(100, 200));
					}
				}
			}
		
		}

		// Turrets - Bombs
		for (it8 = bombList.begin(); it8 != bombList.end(); ++it8)
		{
			if (CheckSphereCollision(*it2, *it8))
			{
				if (Bomb::GetInstance()->GetBombActive())
				{
					(*it2)->SetBuffer(2);
					Money::GetInstance()->SetActiveDestroyed(true);
					Money::GetInstance()->SetIncreaseMoney(Math::RandIntMinMax(100, 200));
					(*it2)->SetIsDone(true);
				}
			}
		}

		// Ensure that the turret is not shooting immediately and if targetPos is not zero.
		if (turret->m_dCoolDown > 0.5 && !targetPos.IsZero() 
			&& (turret->GetType() == 1 || turret->GetType() == 3))
		{
			turret->m_dCoolDown = 0;
			turret->SetFire(true);
			turret->SetFireDestination(targetPos);
			continue;
		}
		else if (turret->m_dCoolDown > 0.1 && !targetPos.IsZero() && turret->GetType() == 2)
		{
			turret->m_dCoolDown = 0;
			turret->SetFire(true);
			turret->SetFireDestination(targetPos);
			continue;
		}
		turret->SetFire(false);
	}
	
	//Cleaning up ENTITIES that are done==========================
	CleanAllList();
	//Updating ENTITIES===========================================
	UpdateAllList(_dt);
}

void EntityManager::UpdateAllList(double _dt)
{
	for (it = entityList.begin(); it != entityList.end(); ++it)
	{
		(*it)->Update(_dt);
	}
	for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
	{
		(*it2)->Update(_dt);
	}
	for (it3 = troopList.begin(); it3 != troopList.end(); ++it3)
	{
		(*it3)->Update(_dt);
	}
	for (it4 = troopProjectileList.begin(); it4 != troopProjectileList.end(); it4++)
	{
		(*it4)->Update(_dt);
	}
	for (it5 = turretProjectileList.begin(); it5 != turretProjectileList.end(); it5++)
	{
		(*it5)->Update(_dt);
	}
	for (it7 = ninjaList.begin(); it7 != ninjaList.end(); it7++)
	{
		(*it7)->Update(_dt);
	}
	// Call Tree class Update function
	for (it_T = TreesList.begin(); it_T != TreesList.end(); it_T++)
	{
		(*it_T)->Update(_dt);
	}
	for (it8 = bombList.begin(); it8 != bombList.end(); it8++)
	{
		(*it8)->Update(_dt);
	}
}

void EntityManager::CleanAllList()
{
	// Delete everything after clean up
	it = entityList.begin();
	it2 = turretList.begin();
	it3 = troopList.begin();
	it4 = troopProjectileList.begin();
	it5 = turretProjectileList.begin();
	it6 = otherList.begin();
	it_T = TreesList.begin();
	it7 = ninjaList.begin();
	it8 = bombList.begin();

	while (it != entityList.end())
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

	while (it2 != turretList.end())
	{
		if ((*it2)->IsDone())
		{
			delete *it2;
			// Remove troop when done
			it2 = turretList.erase(it2);
		}
		else
			// Move on otherwise
			++it2;
	}
	
	while (it3 != troopList.end())
	{
		if ((*it3)->IsDone())
		{
			delete *it3;
			// Remove troop when done
			it3 = troopList.erase(it3);
		}
		else
			// Move on otherwise
			++it3;
	}

	while (it4 != troopProjectileList.end())
	{
		if ((*it4)->IsDone())
		{
			delete *it4;
			it4 = troopProjectileList.erase(it4);
		}
		else
			// Move on otherwise
			++it4;
	}

	while (it5 != turretProjectileList.end())
	{
		if ((*it5)->IsDone())
		{
			delete *it5;
			// Remove turret projectile when done
			it5 = turretProjectileList.erase(it5);
		}
		else
			// Move on otherwise
			++it5;
	}

	while (it6 != otherList.end())
	{
		if ((*it6)->IsDone())
		{
			delete *it6;
			// Remove turret projectile when done
			it6 = otherList.erase(it6);
		}
		else
			// Move on otherwise
			++it6;
	}

	// Trees
	it_T = TreesList.begin();
	while (it_T != TreesList.end())
	{
		if ((*it_T)->IsDone())
		{
			delete *it_T;
			it_T = TreesList.erase(it_T);
		}
		else
			// Move on otherwise
			++it_T;
	}
	//==================== Esdurr touched 25/8/016
	while (it7 != ninjaList.end())
	{
		if ((*it7)->IsDone())
		{
			delete *it7;
			// Remove ninja when done
			it7 = ninjaList.erase(it7);
		}
		else
			// Move on otherwise
			++it7;
	}

	while (it8 != bombList.end())
	{
		if ((*it8)->IsDone())
		{
			delete *it8;
			// Remove turret projectile when done
			it8 = bombList.erase(it8);
		}
		else
			// Move on otherwise
			++it8;
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
	std::list<EntityBase*>::iterator it, it2, it3, it4, it5, it6, it7, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->Render();
	}
	for (it2 = turretList.begin(); it2 != turretList.end(); ++it2)
	{
		(*it2)->Render();
	}
	for (it3 = troopList.begin(); it3 != troopList.end(); ++it3)
	{
		// Normal Troop's Textures
		if (Shield::GetInstance()->GetShieldActive() && (*it3)->GetMeshName() == "testTroop")
			(*it3)->SetMesh(MeshBuilder::GetInstance()->GetMesh("ShieldedTroop"));
		else if ((*it3)->GetMeshName() == "testTroop")
			(*it3)->SetMesh(MeshBuilder::GetInstance()->GetMesh("testTroop"));

		// Archer Troop's Textures
		if (Shield::GetInstance()->GetShieldActive() && (*it3)->GetMeshName() == "testTroop2")
			(*it3)->SetMesh(MeshBuilder::GetInstance()->GetMesh("ShieldedArcherTroop"));
		else if ((*it3)->GetMeshName() == "testTroop2")
			(*it3)->SetMesh(MeshBuilder::GetInstance()->GetMesh("testTroop2"));

		// Tank Troop's Textures
		if (Shield::GetInstance()->GetShieldActive() && (*it3)->GetMeshName() == "testTroop3")
			(*it3)->SetMesh(MeshBuilder::GetInstance()->GetMesh("ShieldedTankTroop"));
		else if ((*it3)->GetMeshName() == "testTroop3")
			(*it3)->SetMesh(MeshBuilder::GetInstance()->GetMesh("testTroop3"));

		(*it3)->Render();
	}
	for (it4 = troopProjectileList.begin(); it4 != troopProjectileList.end(); it4++)
	{
		(*it4)->Render();
	}
	for (it5 = turretProjectileList.begin(); it5 != turretProjectileList.end(); it5++)
	{
		(*it5)->Render();
	}
	for (it6 = otherList.begin(); it6 != otherList.end(); it6++)
	{
		(*it6)->Render();
	}
	for (it7 = ninjaList.begin(); it7 != ninjaList.end(); it7++)
	{
		(*it7)->Render();
	}
	// Call Tree class Render function
	for (it_T = TreesList.begin(); it_T != TreesList.end(); it_T++)
	{
		(*it_T)->Render();
	}
	for (it8 = bombList.begin(); it8 != bombList.end(); it8++)
	{
		(*it8)->Render();
	}
}

//Make this whole thing into a entityManager function. GenerateNinja(GroundEntity *groundEntity , dt)
//after certain time
void EntityManager::GenerateNinja(GroundEntity *groundEntity, double dt)
{
	CNinja3D *ninjaTroop = new CNinja3D;
	ninjaTroop = Create::Ninja3D("ninjaTroop", Vector3(Math::RandFloatMinMax(-50.f, 50.f), 10, Math::RandFloatMinMax(-490.f, -480.f)), Vector3(1, 1, 1));
	ninjaTroop->Init();
	ninjaTroop->SetTerrain(groundEntity);
	ninjaTroop->SetDestination(Vector3(Math::RandFloatMinMax(-60.f, 60.f), 10, Math::RandFloatMinMax(330.f, 350.f)));
	do
	{
		ninjaTroop->SetDestination(Vector3(ninjaTroop->GetFinalDestination().x + Math::RandFloatMinMax(-10.f, 10.f), 10, ninjaTroop->GetFinalDestination().z) + Math::RandFloatMinMax(-10.f, 10.f));
	} while ((ninjaTroop->GetFinalDestination() - Vector3(0, 10, 400)).Length() < 15);
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

void EntityManager::AddNinjaEntity(EntityBase* _newEntity)
{
	ninjaList.push_back(_newEntity);
}

void EntityManager::AddBombEntity(EntityBase* _newEntity)
{
	bombList.push_back(_newEntity);
}

void EntityManager::AddTroopProjectileEntity(EntityBase* _newEntity)
{
	troopProjectileList.push_back(_newEntity);
}

void EntityManager::AddTurretProjectileEntity(EntityBase* _newEntity)
{
	turretProjectileList.push_back(_newEntity);
}

void EntityManager::AddOther(EntityBase* _newEntity)
{
	otherList.push_back(_newEntity);
}

void EntityManager::AddTreesEntity(EntityBase * _newEntity)
{
	TreesList.push_back(_newEntity);
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

	float ObjOneRadius = ThisEntity->GetScale().x + 2 + ThisEntity->GetBuffer();

	float ObjTwoRadius = ThatEntity->GetScale().x + 2 + ThisEntity->GetBuffer();

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
	otherList.clear();
	ninjaList.clear();
	TreesList.clear();
	troopProjectileList.clear();
	turretProjectileList.clear();
}

