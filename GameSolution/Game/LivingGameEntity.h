#pragma once
#ifndef LIVING_GAME_ENTITY_H
#define LIVING_GAME_ENTITY_H
#include <cassert>
#include "GameEntity.h"
#include "GameGlobal.h"

class LivingGameEntity : public GameEntity {
private:
	inline void checkLifeCap() {
		life = (life>maxLife)? maxLife : life;
		life = (life<0)? 0 : life;
	}
	float life;
	float maxLife;
public:
	inline void addHP(float amount) {
		assert(amount>0);
		life+=amount;
		checkLifeCap();
	}
	inline void removeHP(float amount) {
		assert(amount>0);
		life-=amount;
		checkLifeCap();
	}
	inline float getHealthPercent() {
		return life/maxLife;
	}
	inline float getHealth() { return life; }
	inline float getMaxHeath() { return maxLife; }
	inline void  setMaxHealth(float amount) {
		assert(amount>0);
		maxLife = amount;
		checkLifeCap();
	}
};

#endif