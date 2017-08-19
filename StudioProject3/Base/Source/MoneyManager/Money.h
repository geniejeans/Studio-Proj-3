#pragma once
#include "SingletonTemplate.h"

// This class is solely for handling the money
class Money : public Singleton<Money>
{
	// Money player has
	int m_iMoney;
	// Money Rate to increase by
	int m_iMoneyRate;
	// Boolean to set the Money Rain
	bool m_bActive;
	// Duration for Money Rain
	double m_dMoneyOverTime;

public:
	Money();
	~Money();

	//  Initialise this class instance
	void Init();

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

	// Set bool
	void SetActive(bool isTrue);
	// Get bool
	bool GetActive();

	// For events that causes money over time (money rain)
	void UpdateMoney(double dt);

	// For rendering Money on the screen
	void RenderMoney();
};