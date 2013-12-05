#include "EnemyFactory.h"

#include "GameMacros.h"

void EnemyFactory::init(GameSpace *space, GameEntity *player) {
	currentKamikazeEnemy = 0;
	for(uint i=0;i<SIZE_OF_ARRAY(kamikazeEntities);i++) {
		kamikazeEntities[i].init(player,space);
	}
}

KamikazeEnemy *EnemyFactory::getNextKamikazeEnemy() {
	ASSERT(currentKamikazeEnemy<MAX_KAMIKAZE_ENTITIES,"Out of Array Space");
	return &kamikazeEntities[currentKamikazeEnemy++];
}