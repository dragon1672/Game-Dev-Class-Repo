#pragma once

#include "State.h"

class RunningToHomeBase : public State {
	void init(Character * player, GameInstance * ctxt) {
		player->setNewDestPos();
		player->hasFlag = true;
		player->meFlag->holder = player;
		player->meFlag->timeSinceLastMove = std::numeric_limits<float>::infinity();
	}
	void update(Character * player, GameInstance * ctxt) {

	}
};