#include "kamikazeEnemy.h"

void kamikazeEnemy::init(GameEntity *target, GameSpace *mySpace) {
	myLogic.init(this,target,getAcc());
	setSpace(mySpace);
	setMovementLogic(&myLogic);
}