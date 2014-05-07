#pragma once

#include "Character.h" // required
class GameInstance;
class Flag;

class Team {
public:
	GameInstance * gameInstance;
	Character members[2];
	uint numOfPlayers;
	Flag * leFlag;

public:
	Team() : leFlag(nullptr), gameInstance(nullptr), numOfPlayers(0) {}
	void init(GameInstance * ctxt, uint numOfPlayers, glm::mat4 ** transformMats);
	void update(float dt);
	Flag * getFlag();
	glm::vec3 getBase();
	bool hasFlag();
	void respawnAll();
	void registerWithDecisions(DecisionTreeNode * parentNode);
};