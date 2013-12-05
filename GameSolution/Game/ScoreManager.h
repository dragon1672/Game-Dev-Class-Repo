#pragma once
#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include "myAssert.h"
#include "LivingGameEntity.h"
#include "Core.h"

class ScoreManager {
public:
	static const int scoreKillingShip    = 10;
	static const int scoreForKillingBoss = 100;
private:
	int totalPoints;
public:
	ScoreManager() {
		totalPoints = 0;
	}
	void LivingEntityDeath(LivingGameEntity * thatDied);
	int getTotalPoints();
	void addPoints(int amount);
	void spendPoints(int amount);
	void resetPoints();
	void draw(MyGraphics& graphics, Vector2D& pos, int size, Core::RGB color);
};

#endif