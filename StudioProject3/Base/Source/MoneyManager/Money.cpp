#include "Money.h"
#include <iostream>

Money::Money()
	: m_iMoney(0)
	, m_iMoneyRate(10)
	, m_bActive(false)
	, m_dMoneyOverTime(0.0)
{
}

Money::~Money()
{

}

void Money::Init()
{
	m_iMoney = 0;
}

void Money::SetMoney(int money)
{
	this->m_iMoney = money;
}

int Money::GetMoney()
{
	return m_iMoney;
}

void Money::SetMoneyRate(int rate)
{
	this->m_iMoneyRate = rate;
}

int Money::GetMoneyRate()
{
	return m_iMoneyRate;
}

void Money::SetMoneyOverTime(double time)
{
	this->m_dMoneyOverTime = time;
}

double Money::GetMoneyOverTime()
{
	return m_dMoneyOverTime;
}

void Money::SetActive(bool isTrue)
{
	this->m_bActive = isTrue;
}

bool Money::GetActive()
{
	return m_bActive;
}

void Money::UpdateMoney(double dt)
{
	m_dMoneyOverTime += dt;
	if (m_dMoneyOverTime > 5.0)
	{
		m_iMoney += m_iMoneyRate;
		m_dMoneyOverTime = 0;
	}

	//if (m_bActive)
	//{
	//	m_dMoneyOverTime += (double)5 * dt;
	//	if (m_dMoneyOverTime > 10.0)
	//	{
	//		m_dMoneyOverTime = 0.0;
	//	}
	//}
}

void Money::RenderMoney()
{
}
