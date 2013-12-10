#pragma once
#ifndef LIVING_GAME_ENTITY_H
#define LIVING_GAME_ENTITY_H
#include "GameEntity.h"
#include "myAssert.h"

class LivingGameEntity : public GameEntity {
private:
	void checkLifeCap();
	float life;
	float maxLife;
public:
	void  initFullHealth(float amount);
	void  addHP(float amount);
	void  removeHP(float amount);
	float getHealthPercent();
	float getHealth();
	float getMaxHeath();
	void  setMaxHealth(float amount);
	bool  isAlive();
	void  collisionDamage(LivingGameEntity * collidedWith);
};

#endif