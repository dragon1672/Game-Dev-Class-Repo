#include "GameEnemyHandler.h"
#include "MyRandom.h"
#include "GameSpace.h"


void GameEnemyHandler::init(GameSpace *space, GameEntity *player) {
	LOG(Info,"Spawner Init",0);
	this->space = space;
	myFactory.init(space,player);
	numberOfEntitiesSpawned = 0;
	entitySpawnClock.start();
}
int  GameEnemyHandler::getFreeArraySpot() {
	if(numberOfEntitiesSpawned<SIZE_OF_ARRAY(activeEnemies)) return numberOfEntitiesSpawned;
	for(uint i=0;i<SIZE_OF_ARRAY(activeEnemies);i++)
		if(!activeEnemies[i]->isAlive())
			return i;
	return -1;
}
void GameEnemyHandler::spawnEntity() {
	//if(entitySpawnClock.getCurrentTime()>5) {//time to spawn a new entity
	if(entitySpawnClock.getCurrentTime()>delayBetweenEntitySpawns) {//time to spawn a new entity
		int index = getFreeArraySpot();
		if(index>=0) {//otherwise all active spots are accounted for
			activeEnemies[index] = myFactory.getNextKamikazeEnemy();
			//activeEnemies[index]->setPosition(space->randomOutOfBoundWorldPoint());
			activeEnemies[index]->setPosition(space->randomOutOfBoundWorldPoint());
			space->addLivingEntity(activeEnemies[index]);
			//resetVars
			entitySpawnClock.start();
			numberOfEntitiesSpawned++;
			delayBetweenEntitySpawns = delayBetweenEntitySpawnsDecreaseScaler * Random::randomFloat(delayBetweenEntitySpawns, delayBetweenEntitySpawns+delayBetweenEntitySpawnsRange);
		}
	}
}
void GameEnemyHandler::update(float dt) {
	dt;
	spawnEntity();
}