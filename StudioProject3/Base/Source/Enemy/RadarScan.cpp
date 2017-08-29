#include "RadarScan.h"
#include <iostream>
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
		m_fRadarCooldown += (float)dt;

	else if (m_fRadarCooldown >= 20.f)
	{
		m_bRadarOnCooldown = false;
		m_fRadarCooldown = 0.0f;
	}

}

