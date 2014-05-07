#pragma once

#include "Character.h"
class GameInstance;

class Team {
	GameInstance * gameInstance;
	Character members[2];
	uint numOfPlayers;
	Flag * leFlag;

public:

	void init(GameInstance * ctxt, uint numOfPlayers, glm::mat4 ** transformMats);
	void update(float dt);
	Flag * getFlag();
	glm::vec3 getBase();
	bool hasFlag();
};