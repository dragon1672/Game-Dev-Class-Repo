#pragma once
#ifndef KAMIKAZE_ENEMY_H
#define KAMIKAZE_ENEMY_H

#include "Enemy.h"
#include "TargetShipMoveLogic.h"

class KamikazeEnemy : public Enemy {
	TargetShipMoveLogic myLogic;
public:
	void init(GameEntity *target, GameSpace *mySpace);
};

#endif
