#pragma once
#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "kamikazeEnemy.h"

class EnemyFactory {
	static const int MAX_KAMIKAZE_ENTITIES = 100;
	kamikazeEnemy kamikazeEntities[MAX_KAMIKAZE_ENTITIES];
	int currentKamikazeEnemy;
public:
	void init(GameSpace *space, GameEntity *player);
	kamikazeEnemy *getNextKamikazeEnemy();
};

#endif