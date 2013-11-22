#include "GameGlobal.h"
#include "EnemyFactory.h"
#include <cassert>


void EnemyFactory::init(GameSpace *space, GameEntity *player) {
	currentKamikazeEnemy = 0;
	for(uint i=0;i<SIZE_OF_ARRAY(kamikazeEntities);i++) {
		kamikazeEntities[i].init(player,space);
	}
}

kamikazeEnemy *EnemyFactory::getNextKamikazeEnemy() {
	MY_ASSERT(currentKamikazeEnemy<MAX_KAMIKAZE_ENTITIES);
	return &kamikazeEntities[currentKamikazeEnemy++];
}