#include "MoneyRain.h"
#include "GLFW\glfw3.h"
#include <iostream>

#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "../EntityManager.h"
#include "../GroundEntity.h"

MoneyRain::MoneyRain()
	: _pos(0.f, 0.f, 0.f)
	, _scale(0.f, 0.f, 0.f)
	, _vel(0.f, 0.f, 0.f)
	, _Gravity(0.f, -9.8f, 0.f)
	, m_fSpeed(10.f)
	, m_bFall(false)
{
}

MoneyRain::MoneyRain(Mesh * _modelMesh)
{
	modelmesh = _modelMesh;
}

MoneyRain::~MoneyRain()
{
}

void MoneyRain::Init(void)
{
	_pos.Set(0.f, 490.f,0.f);
	_scale.Set(10.f, 10.f, 1.f);
	_vel.Set(0.f, 0.f, 0.f);

	//Physics
	m_fSpeed = 10.f;
	_Gravity.Set(0.f, -9.8f, 0.f);
}

void MoneyRain::SetPos(Vector3 & _value)
{
	_pos = _value;
}

Vector3 MoneyRain::GetPos()
{
	return _pos;
}

void MoneyRain::setScale(Vector3 & _value)
{
	_scale = _value;
}

Vector3 MoneyRain::GetScale()
{
	return _scale;
}

void MoneyRain::SetVel(Vector3 & _value)
{
	_vel = _value;
}

Vector3 MoneyRain::GetVel()
{
	return _vel;
}

void MoneyRain::SetFall(bool _isTrue)
{
	this->m_bFall = _isTrue;
}

bool MoneyRain::GetFall()
{
	return m_bFall;
}

void MoneyRain::Update(double dt)
{
	//if (m_bFall)
	//{
	//	//for (int i = 0; i < 50; ++i)
	//	//{
	//		// update velocity
	//		Init();
	//		_vel += _Gravity * m_fSpeed * dt;
	//		_pos.y += _vel.y * m_fSpeed * dt;
	//		std::cout << _pos << std::endl;
	//		//SetPos(Vector3(_pos.x, _pos.y, _pos.z));
	//	//}
	//}
}

void MoneyRain::Render()
{
	glEnable(GL_BLEND);
	// Activate the Blend Function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	//modelStack.Rotate(Math::RadianToDegree(atan2(thePlayer->GetInstance()->GetPos().x - _pos.x,
	//	 thePlayer->GetInstance()->GetPos().z - _pos.z)), 0, 1, 0);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelmesh);
	modelStack.PopMatrix();

	glDisable(GL_BLEND);
}

MoneyRain * Create::Money(const std::string & _meshName, const Vector3 & position, const Vector3 & scale, Vector3 & velocity)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	MoneyRain* result = new MoneyRain(modelMesh);
	result->SetMeshName(_meshName);
	result->SetPosition(position);
	result->SetScale(scale);
	result->SetVel(velocity);
	EntityManager::GetInstance()->AddEntity(result);
	return result;
}
