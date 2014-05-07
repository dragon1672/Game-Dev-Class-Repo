#include "RandomPathState.h"
#include "Character.h"
#include "Team.h"
#include "GameInstance.h"
#include "MyRandom.h"

void STATES::RandomPathState::init(Character * leDude) {
	if(leDude->path.isComplete()) {
		leDude->setNewDestPos(Random::glmRand::randomFloatVectorInBoxRanged(30,0,100));
	}
}

void STATES::RandomPathState::update(Character * leDude) {
	init(leDude);
}