#pragma once
#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "KamikazeEnemy.h"

class EnemyFactory {
	static const int MAX_KAMIKAZE_ENTITIES = 100;
	KamikazeEnemy kamikazeEntities[MAX_KAMIKAZE_ENTITIES];
	int currentKamikazeEnemy;
public:
	void init(GameSpace *space, GameEntity *player);
	KamikazeEnemy *getNextKamikazeEnemy();
	int enemiesLeft();
};

#endif