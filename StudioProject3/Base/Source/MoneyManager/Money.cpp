#include "Money.h"
#include <iostream>
using namespace std;

Money::Money()
	: m_iMoney(0)
	, m_iMoneyRate(10)
	, m_bActiveRain(false)
	, m_bActiveStorm(false)
	, m_dMoneyOverTime(0.0)
	, theMoneyRain(NULL)
	, theThunderStorm(NULL)
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

void Money::SetActiveRain(bool isTrue)
{
	this->m_bActiveRain = isTrue;
}

void Money::SetActiveStorm(bool isTrue)
{
	this->m_bActiveStorm = isTrue;
}

bool Money::GetActiveRain()
{
	return m_bActiveRain;
}

bool Money::GetActiveStorm()
{
	return m_bActiveStorm;
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
	if (m_bActiveRain)
	{
		m_dMoneyOverTime += 5 * dt;

		if (m_dMoneyOverTime > 1.5)
		{
				m_iMoney += m_iMoneyRate;
				m_dMoneyOverTime = 0;
		}
	}

	// ============ Money Decreases when Thunder Storm is active ========================= //
	if (m_bActiveStorm)
	{
		m_dMoneyOverTime += 5 * dt;

		if (m_dMoneyOverTime > 1.5)
		{
			m_iMoney -= (m_iMoneyRate * 0.5f);
			m_dMoneyOverTime = 0;
		}
	}
}
