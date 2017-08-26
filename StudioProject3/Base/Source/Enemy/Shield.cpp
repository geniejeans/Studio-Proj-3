// Player's Troops Shield.

#include "Shield.h"

Shield::Shield() :
	m_bShieldActive(false),
	elapsedTime(0)
{
}

Shield::~Shield()
{
}

void Shield::Update(double dt)
{
	//check shield is active
	if (m_bShieldActive)
	{
		//start timer
		elapsedTime += dt;
		if (elapsedTime >2)
		{
			//if timer is more then 2 sec set to false
			m_bShieldActive = false;
		}
	}
	else
		elapsedTime = 0;
}

void Shield::SetShieldActive()
{
	this->m_bShieldActive = true;
}

bool Shield::GetShieldActive()
{
	return m_bShieldActive;
}
