#pragma once

#include "State.h"
#include "Character.h"
#include "Team.h"

namespace STATES {

class FetchingFlag : public State {
public:
	void init(Character * player) {

	}
	void update(Character * player) {
		float errorRadius = .5f;
		glm::vec3 flagPos = player->myTeam->getFlag()->pos;
		glm::vec3 playerPos = player->pos;
		glm::vec3 diff = playerPos - flagPos;
		float length = glm::dot(diff,diff);
		if(errorRadius * errorRadius > length) { // we are close enough to the flag to grab
			player->hasFlag = player->myTeam->getFlag()->grab(player);
		}
	}
};

}