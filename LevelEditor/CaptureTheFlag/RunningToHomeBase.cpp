#include "RunningToHomeBase.h"
#include "Character.h"
#include "Team.h"
#include "GameInstance.h"

void STATES::RunningToHomeBase::init(Character * leDude, State * lastState) {
	
	if(lastState != this) {
		leDude->setNewDestPos(leDude->myTeam->getBase());
	}
}

void STATES::RunningToHomeBase::update(Character * leDude) {
	float errorRadius = .5f;
	glm::vec3 basePos = leDude->myTeam->getBase();
	glm::vec3 playerPos = leDude->pos;
	glm::vec3 diff = playerPos - basePos;
	float length = glm::dot(diff,diff);
	if(errorRadius * errorRadius > length) { // we are close enough to the flag to grab
		leDude->myTeam->gameInstance->scorePoint(leDude);
	}
}