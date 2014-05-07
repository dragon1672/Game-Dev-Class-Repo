#include "Team.h"
#include "GameInstance.h"

void Team::init(GameInstance * ctxt, uint numOfPlayers, glm::mat4 ** transformMats) {
	this->numOfPlayers = numOfPlayers;
	for (int i = 0; i < numOfPlayers; i++)
	{
		members[i].init(transformMats[i],this);
	}
}
void Team::update(float dt) {
	for (int i = 0; i < numOfPlayers; i++)
	{
		members[i].update(dt);
	}
}
Flag * Team::getFlag() {
	return &gameInstance->theEpicFlag;
}
glm::vec3 Team::getBase() {
	return gameInstance->getMyBasePos(this);
}
bool Team::hasFlag() {
	bool ret = false;
	for (int i = 0; i < numOfPlayers && ! ret; i++)
	{
		ret = members[i].hasFlag;
	}
	return ret;
}