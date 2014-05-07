#pragma once

#include "State.h"

namespace STATES {

class RunningToHomeBase : public STATES::State {
public:
	void init(Character * player) {
		/*
		player->setNewDestPos(player->myTeam->getBase());
		player->hasFlag = true;
		player->myTeam->getFlag()->grab(player);
		//*/
	}
	void update(Character * player) {

	}
};

}