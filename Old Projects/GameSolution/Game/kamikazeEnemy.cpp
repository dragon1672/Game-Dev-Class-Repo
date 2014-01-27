#include "KamikazeEnemy.h"

void KamikazeEnemy::init(GameEntity *target, GameSpace *mySpace) {
	myLogic.init(this,target,getAcc());
	setSpace(mySpace);
	setMovementLogic(&myLogic);
}