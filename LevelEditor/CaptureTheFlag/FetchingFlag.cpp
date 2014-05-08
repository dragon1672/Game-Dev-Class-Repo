#include "FetchingFlag.h"
#include "Character.h"
#include "Team.h"
#include "GameInstance.h"

void STATES::FetchingFlag::init(Character * leDude, State * lastState) {
	lastState;//don't care
	leDude->setNewDestPos(leDude->getFlag()->pos);
}

void STATES::FetchingFlag::update(Character * leDude) {
	float errorRadius = .5f;
	glm::vec3 flagPos = leDude->getFlag()->pos;
	glm::vec3 playerPos = leDude->pos;
	glm::vec3 diff = playerPos - flagPos;
	float length = glm::dot(diff,diff);
	if(errorRadius * errorRadius > length) { // we are close enough to the flag to grab
		leDude->hasFlag = leDude->getFlag()->grab(leDude);
	}
}