#include "Team.h"
#include "GameInstance.h"

void Team::init(GameInstance * ctxt, uint numOfPlayers, glm::mat4 ** transformMats) {
	this->gameInstance = ctxt;
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
	for (int i = 0; i < numOfPlayers; i++)
	{
		if(members[i].hasFlag) return true;
	}
	return false;
}
void Team::respawnAll() {
	for (int i = 0; i < numOfPlayers; i++)
	{
		members[i].respawn();
	}
}
void Team::registerWithDecisions(DecisionTreeNode * parentNode) {
	for (int i = 0; i < numOfPlayers; i++)
	{
		members[i].theSmartTree = parentNode;
	}
}

bool vecInCircleRange(glm::vec3& pos1, glm::vec3& pos2, float errorRadius=.5f) {
	glm::vec3 diff = pos1 - pos2;
	float length = glm::dot(diff,diff);
	return (errorRadius * errorRadius > length);
}
bool Team::collision(glm::vec3& toCheck, float radOfCheck, float radOfMembers) {
	for (int i = 0; i < numOfPlayers; i++)
	{
		if(vecInCircleRange(toCheck,members[i].pos,radOfCheck + radOfMembers)) return true;
	}
	return false;
}