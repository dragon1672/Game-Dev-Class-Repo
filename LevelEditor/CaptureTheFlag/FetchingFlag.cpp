#include "FetchingFlag.h"
#include "Character.h"
#include "Team.h"
#include "GameInstance.h"

void STATES::FetchingFlag::init(Character * leDude, State * lastState) {
	lastState;//don't care
	glm::vec3 pos;
	if(leDude->getFlag()->holder!=nullptr) {
		pos = leDude->getFlag()->holder->pos;
	} else {
		pos = leDude->getFlag()->pos;
	}
	leDude->setNewDestPos(pos);
}

void STATES::FetchingFlag::update(Character * leDude) {
	if(leDude->getFlag()->holder!=nullptr) {
		if(leDude->myTeam->hasFlag()) {
			leDude->runDecisionTree();
		} else {
			init(leDude,nullptr);
		}
	} else {
		float errorRadius = 1;
		glm::vec3 flagPos = leDude->getFlag()->pos;
		glm::vec3 playerPos = leDude->pos;
		glm::vec3 diff = playerPos - flagPos;
		float length = glm::dot(diff,diff);
		if(errorRadius * errorRadius > length) { // we are close enough to the flag to grab
			leDude->hasFlag = leDude->getFlag()->grab(leDude);
		}
	}
}