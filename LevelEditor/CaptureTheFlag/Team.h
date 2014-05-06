#pragma once

#include "Character.h"
class GameInstance;

class Team {
	GameInstance * gameInstance;
	Character members[2];
	uint numOfPlayers;
	Flag * leFlag;

public:

	void init(GameInstance * ctxt, uint numOfPlayers, glm::mat4 ** transformMats) {
		this->numOfPlayers = numOfPlayers;
		for (int i = 0; i < numOfPlayers; i++)
		{
			members[i].init(transformMats[i],this);
		}
	}
	void update(float dt) {
		for (int i = 0; i < numOfPlayers; i++)
		{
			members[i].update(dt);
		}
	}
	Flag * getFlag() {
		return &gameInstance->theEpicFlag;
	}
	glm::vec3 getBase() {
		return gameInstance->getMyBasePos(this);
	}
};