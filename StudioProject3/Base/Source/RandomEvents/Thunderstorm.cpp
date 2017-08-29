#include "ThunderStorm.h"
#include "GLFW\glfw3.h"
#include <iostream>

#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "../EntityManager.h"
#include "../GroundEntity.h"
#include "../MoneyManager/Money.h"

Thunderstorm::Thunderstorm()
	: _pos(0.f, 0.f, 0.f)
	, _scale(0.f, 0.f, 0.f)
	, _vel(0.f, 0.f, 0.f)
	, _Gravity(0.f, -9.8f, 0.f)
	, m_fSpeed(10.f)
	, m_bFall(false)
{
}

Thunderstorm::Thunderstorm(Mesh * _modelMesh)
{
	modelmesh = _modelMesh;
	Init();
}

Thunderstorm::~Thunderstorm()
{
}

void Thunderstorm::Init(void)
{
	_pos.Set(Math::RandFloatMinMax(500.0f, -500.0f), 510.f, Math::RandFloatMinMax(500.0f, -500.0f));
	_scale.Set(20.f, 20.f, 1.f);
	_vel.Set(0.f, 0.f, 0.f);

	//Physics
	m_fSpeed = 4.f;
	_Gravity.Set(0.f, -9.8f, 0.f);

}

void Thunderstorm::SetPos(Vector3 & _value)
{
	this->_pos = _value;
}

Vector3 Thunderstorm::GetPos()
{
	return _pos;
}

void Thunderstorm::setScale(Vector3 & _value)
{
	this->_scale = _value;
}

Vector3 Thunderstorm::GetScale()
{
	return _scale;
}

void Thunderstorm::SetVel(Vector3 & _value)
{
	this->_vel = _value;
}

Vector3 Thunderstorm::GetVel()
{
	return  _vel;
}

void Thunderstorm::SetFall(bool _isTrue)
{
	this->m_bFall = _isTrue;
}

bool Thunderstorm::GetFall()
{
	return m_bFall;
}

void Thunderstorm::Update(double dt)
{
	if (m_bFall == true)
	{
		Money::GetInstance()->SetActiveStorm(true);

		_vel += _Gravity * m_fSpeed * (float)dt;
		_pos.y += _vel.y * m_fSpeed * (float)dt;

		SetPosition(_pos);
	}
	else if (m_bFall == false)
	{
		Money::GetInstance()->SetActiveStorm(false);

		SetPos(Vector3(_pos.x, 510.f, _pos.z));
		SetPosition(GetPos());
		_vel.SetZero();
	}
}

void Thunderstorm::Render()
{
	glEnable(GL_BLEND);
	// Activate the Blend Function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelmesh);
	modelStack.PopMatrix();

	glDisable(GL_BLEND);
}

Thunderstorm * Create::Storm(const std::string & _meshName, const Vector3 & position, const Vector3 & scale, Vector3 & velocity)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	Thunderstorm* result = new Thunderstorm(modelMesh);
	result->SetMeshName(_meshName);
	result->SetPosition(position);
	result->SetScale(scale);
	result->SetVel(velocity);
	EntityManager::GetInstance()->AddEntity(result);
	return result;
}
