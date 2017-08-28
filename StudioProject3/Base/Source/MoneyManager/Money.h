#pragma once
#include "SingletonTemplate.h"
#include "../RandomEvents/MoneyRain.h"
#include "../RandomEvents/Thunderstorm.h"

// This class is solely for handling the money
class Money : public Singleton<Money>
{
	// Money player has
	int m_iMoney;
	// Money Rate to increase by
	int m_iMoneyRate;
	// Boolean to set the Money Rain
	bool m_bActiveRain;
	// Boolean to set the Thunder Storm
	bool m_bActiveStorm;
	// Duration for Money Increase
	double m_dMoneyOverTime;
	// Bool to increase when environment destroyed
	bool m_bActiveDestroyed;
	// Amount to increase by 
	int m_iIncreaseMoney;
	// Money Price Rate for the Shield
	int m_iShieldPriceRate;
	MoneyRain* theMoneyRain;
	Thunderstorm* theThunderStorm;

public:
	Money();
	~Money();

	// Set Money
	void SetMoney(int money);
	// Get Money
	int GetMoney();
	//Decrease the money
	void DeductMoney(int value);

	// Set Money Rate
	void SetMoneyRate(int rate);
	// Get Money Rate
	int GetMoneyRate();

	// Set Money Over Time
	void SetMoneyOverTime(double time);
	// Get Money over time
	double GetMoneyOverTime();

	// Set bool
	void SetActiveRain(bool isTrue);
	void SetActiveStorm(bool isTrue);

	// Get bool
	bool GetActiveRain();
	bool GetActiveStorm();

	//Shield=====
	// Set Shield Price Rate
	void SetShieldPriceRate(int rate);
	// Get Shield Price Rate
	int GetShieldPriceRate();

	// Set the Cool Down Timer
	void SetCoolDownTime(double time);
	// Get the Cool Down Timer
	double GetCoolDownTime();
	//Shield======
	// Set Amount to increase by
	void SetIncreaseMoney(int increase);
	// Get Amount increased by
	int GetIncreasedMoney();

	void SetActiveDestroyed(bool isTrue);
	bool GetActiveDestroyed();

	// For events that causes money over time (money rain)
	void UpdateMoney(double dt);
};