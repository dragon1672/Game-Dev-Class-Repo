#pragma once
#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include "myAssert.h"

class ScoreManager {
public:
	static const int scoreKillingShip    = 10;
	static const int scoreForKillingBoss = 100;
private:
	int totalPoints;
public:
	void kilBoss();
	void killEnemy();
	inline int getTotalPoints() {
		return totalPoints;
	}
	inline void addPoints(int amount) {
		ASSERT(amount>0,"trying to pass a neg amount of points to add");
		totalPoints += amount;
	}
	inline void spendPoints(int amount) {
		ASSERT(amount>0,"trying to pass a neg amount of points to spend");
		totalPoints -= amount;
	};
	inline void resetPoints() {
		totalPoints = 0;
	}
};

#endif