#include "Money.h"
#include <iostream>
using namespace std;

Money::Money()
	: m_iMoney(0)
	, m_iMoneyRate(10)
	, m_bActive(false)
	, m_dMoneyOverTime(0.0)
	, m_dMoneyRainDuration(0.0)
	, theMoneyRain(NULL)
{
}

Money::~Money()
{

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

void Money::SetMoneyRainDuration(double time)
{
	this->m_dMoneyRainDuration = time;
}

double Money::GetMoneyRainDuration()
{
	return m_dMoneyRainDuration;
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
	// ============ Generate money over time ============= //
	m_dMoneyOverTime += dt;
	if (m_dMoneyOverTime > 3.0)
	{
		m_iMoney += m_iMoneyRate;
		m_dMoneyOverTime = 0;
	}

	// ============ Generate Money at a faster rate when Money Rain is active ============= //
	if (m_bActive)
	{
		m_dMoneyOverTime += 5 * dt;

		if (m_dMoneyOverTime > 1.5)
		{
				m_iMoney += m_iMoneyRate;
				m_dMoneyOverTime = 0;
		}
	}
}
