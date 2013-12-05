#include "GameEnemyHandler.h"

#include "GameMacros.h"

#include "MyRandom.h"
#include "GameSpace.h"


void GameEnemyHandler::init(GameSpace *space, GameEntity *player) {
	LOG(Info,"Spawner Init",0);
	this->space = space;
	resetArray();
	myFactory.init(space,player);
	numberOfEntitiesSpawned = 0;
	entitySpawnClock.start();
	isEmpty = false;
}
void GameEnemyHandler::resetArray() {
	for(uint i=0;i<SIZE_OF_ARRAY(activeEnemies) && i < numberOfEntitiesSpawned;i++)
		activeEnemies[i]->setMaxHealth(activeEnemies[i]->getMaxHeath());//resetting health
}
int  GameEnemyHandler::getFreeArraySpot() {
	if(numberOfEntitiesSpawned<SIZE_OF_ARRAY(activeEnemies)) return numberOfEntitiesSpawned;
	for(uint i=0;i<SIZE_OF_ARRAY(activeEnemies);i++)
		if(!activeEnemies[i]->isAlive())
			return i;
	return -1;
}
void GameEnemyHandler::spawnEntity() {
	if(entitySpawnClock.getCurrentTime()>delayBetweenEntitySpawns) {//time to spawn a new entity
		int index = getFreeArraySpot();
		if(index>=0) {//Free spot or has player hit maxEntities
			if(myFactory.enemiesLeft()>1) {
				activeEnemies[index] = myFactory.getNextKamikazeEnemy();
				activeEnemies[index]->setPosition(space->randomOutOfBoundWorldPoint());
				space->addLivingEntity(activeEnemies[index]);
				//resetVars
				numberOfEntitiesSpawned++;
				delayBetweenEntitySpawns = delayBetweenEntitySpawnsDecreaseScaler * Random::randomFloat(delayBetweenEntitySpawns, delayBetweenEntitySpawns+delayBetweenEntitySpawnsRange);
			} else {//factory is out of enemies
				isEmpty = true;
			}
		}
		//always reset the clock for effeciency (so array is searched every update if player has hit cap)
		entitySpawnClock.start();
	}
}
void GameEnemyHandler::update(float dt) {
	dt;
	spawnEntity();
}
bool GameEnemyHandler::hasBeenDefeated() {
	return isEmpty;
}