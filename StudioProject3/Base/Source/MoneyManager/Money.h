#pragma once
#include "SingletonTemplate.h"
#include "../RandomEvents/MoneyRain.h"

// This class is solely for handling the money
class Money : public Singleton<Money>
{
	// Money player has
	int m_iMoney;
	// Money Rate to increase by
	int m_iMoneyRate;
	// Boolean to set the Money Rain
	bool m_bActive;
	// Duration for Money Increase
	double m_dMoneyOverTime;
	// Duration for Money Rain
	double m_dMoneyRainDuration;

	MoneyRain* theMoneyRain;

public:
	Money();
	~Money();

	// Set Money
	void SetMoney(int money);
	// Get Money
	int GetMoney();

	// Set Money Rate
	void SetMoneyRate(int rate);
	// Get Money Rate
	int GetMoneyRate();

	// Set Money Over Time
	void SetMoneyOverTime(double time);
	// Get Money over time
	double GetMoneyOverTime();

	// Set Money Rain Duration
	void SetMoneyRainDuration(double time);
	// Get Money Rain Duration
	double GetMoneyRainDuration();

	// Set bool
	void SetActive(bool isTrue);
	// Get bool
	bool GetActive();

	// For events that causes money over time (money rain)
	void UpdateMoney(double dt);
};