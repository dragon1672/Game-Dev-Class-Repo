#pragma once

#include "State.h"
#include "Character.h"

namespace STATES {

class RunningToHomeBase : public State {
public:
	void init(Character * player) {
		player->setNewDestPos(player->myTeam->getBase());
		player->hasFlag = true;
		player->myTeam->getFlag()->grab(player);
	}
	void update(Character * player) {

	}
};

}