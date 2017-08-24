#pragma once
#include "SingletonTemplate.h"

class RadarScan : public Singleton<RadarScan>
{
private:
	bool isRpressed = false;
public:
	RadarScan() {};
	~RadarScan() {};
	void SetRPressed(bool _value);
	bool GetRPressed();
};