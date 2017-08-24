#ifndef THUNDER_STORM_H	
#define THUNDER_STORM_H

#include "RandomEvents.h"
#include "../PlayerInfo/PlayerInfo.h"

class Mesh;

class Thunderstorm : public RandomEvents, public EntityBase
{
	Vector3 _pos, _scale, _vel, _Gravity;
	Mesh* modelmesh;

	bool m_bFall;

	float m_fSpeed;

public:
	Thunderstorm();
	Thunderstorm(Mesh* _modelMesh);
	~Thunderstorm();

	void Init(void);
	void Update(double dt);
	void Render();

	// Position
	void SetPos(Vector3& _value);
	Vector3 GetPos();

	// Scale
	void setScale(Vector3& _value);
	Vector3 GetScale();

	// Vel
	void SetVel(Vector3& _value);
	Vector3 GetVel();

	// Fall
	void SetFall(bool _isTrue);
	bool GetFall();
};

namespace Create
{
	Thunderstorm* Storm(const std::string& _meshName
		, const Vector3& position
		, const Vector3& scale
		, Vector3& velocity = Vector3(0.0f, 0.f, 0.f));
};

#endif