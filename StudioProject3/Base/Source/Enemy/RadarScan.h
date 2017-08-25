#pragma once
#include "SingletonTemplate.h"

class RadarScan : public Singleton<RadarScan>
{
private:
	bool isRpressed = false;
	bool m_bRadarOnCooldown = false;
	float m_fRadarDuration = 0.0f;
	float m_fRadarCooldown = 0.0f;
public:
	RadarScan() {};
	~RadarScan() {};
	void SetRPressed(bool _value);
	bool GetRPressed();
	bool GetCooldown();
	void Update(double dt);
};