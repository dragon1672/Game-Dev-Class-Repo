#pragma once
#ifndef GAME_ENEMY_HANDLER_H
#define GAME_ENEMY_HANDLER_H

#include "EnemyFactory.h"
#include "Timer.h"

class GameEnemyHandler {
private:
	static const int MAX_ACTIVE_ENTITIES = 10;
	float delayBetweenEntitySpawnsDecreaseScaler;
	float delayBetweenEntitySpawnsRange;
	EnemyFactory myFactory;
	GameSpace *space;
	Enemy *activeEnemies[MAX_ACTIVE_ENTITIES];//pointers to current activeEntities
	int numberOfEntitiesSpawned;
	
	Timer entitySpawnClock;
	float delayBetweenEntitySpawns;
public:
	GameEnemyHandler() {
		delayBetweenEntitySpawnsDecreaseScaler = .7f;
		delayBetweenEntitySpawnsRange = 1;
		delayBetweenEntitySpawns = 5;
	}
	void init(GameSpace *space, GameEntity *player);
	int  getFreeArraySpot();
	void spawnEntity();
	void update(float dt);
};

#endif