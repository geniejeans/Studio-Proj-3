#include "RadarScan.h"
#include <iostream>
#include "../SoundEngine.h"

void RadarScan::SetRPressed(bool _value)
{
	isRpressed = _value;
}

bool RadarScan::GetRPressed()
{
	return isRpressed;
}

bool RadarScan::GetCooldown()
{
	return m_bRadarOnCooldown;
}

int RadarScan::GetDuration()
{
	return m_fRadarDuration;
}

void RadarScan::Update(double dt)
{
	if (isRpressed)
	{
		m_fRadarDuration += (float)dt;
		if (m_fRadarDuration >= 10.f)
		{
			isRpressed = false;
			m_fRadarDuration = 0.0f;
			m_bRadarOnCooldown = true;
		}
	}

	if (m_bRadarOnCooldown && m_fRadarCooldown <= 20.f)
	{
		m_fRadarCooldown += (float)dt;
	}
	else if (m_fRadarCooldown >= 20.f)
	{
		m_bRadarOnCooldown = false;
		m_fRadarCooldown = 0.0f;
		CSoundEngine::GetInstance()->Init();
		CSoundEngine::GetInstance()->AddSound("Radar_Abled", "Image//Sounds/Radar_Abled.mp3");
		CSoundEngine::GetInstance()->PlayASound("Radar_Abled", false);

	}
	if (isRpressed && !m_bRadarOnCooldown && m_fRadarDuration <= 0.08f)
	{
		CSoundEngine::GetInstance()->Init();
		CSoundEngine::GetInstance()->AddSound("Radar_Used", "Image//Sounds/Radar_Used.mp3");
		CSoundEngine::GetInstance()->PlayASound("Radar_Used", false);

	}
	//std::cout << m_fRadarDuration << std::endl;
}
