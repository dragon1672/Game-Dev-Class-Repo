#include "GameInstance.h"

#include "MyRandom.h"
#include "glm/gtx/transform.hpp"

void GameInstance::init(AStar::DEBUG::AStarDebugPathGenerator& pather, DebugShapeManager& shaper, uint numOfPlayersPerTeam, glm::mat4 ** teamARenderableTransforms, glm::mat4 ** teamBRenderableTransforms, glm::mat4 * flagRenderableTransform) {
	this->shaper = &shaper;
	this->pather = &pather;
	theEpicFlag.init(flagRenderableTransform); 
	theATeam.init(this,numOfPlayersPerTeam,teamARenderableTransforms);
	theBTeam.init(this,numOfPlayersPerTeam,teamBRenderableTransforms);
}
void GameInstance::registerBaseTransforms(glm::mat4 * teamAHomeBaseTransform, glm::mat4 * teamBHomeBaseTransform) {
	this->teamAHomeBaseTransform = teamAHomeBaseTransform;
	this->teamBHomeBaseTransform = teamBHomeBaseTransform;
	*(teamAHomeBaseTransform) = glm::translate(teamAHomeBase);
	*(teamBHomeBaseTransform) = glm::translate(teamBHomeBase);
}
void GameInstance::randomSetBases(GameNode * nodes, uint numOfNodes) {
	int randomIndexForA = Random::randomInt(0,numOfNodes);
	int randomIndexForB = Random::randomInt(0,numOfNodes);
	teamAHomeBase = nodes[randomIndexForA].pos;
	teamBHomeBase = nodes[randomIndexForB].pos;
	if(teamAHomeBaseTransform!= nullptr) *(teamAHomeBaseTransform) = glm::translate(teamAHomeBase);
	if(teamBHomeBaseTransform!= nullptr) *(teamBHomeBaseTransform) = glm::translate(teamBHomeBase);
}
void GameInstance::update(float dt) {
	theEpicFlag.update(dt);
	theATeam.update(dt);
	theBTeam.update(dt);
}
glm::vec3 GameInstance::getMyBasePos(Team * myTeam) {
	return (myTeam == &theATeam)? teamAHomeBase : teamBHomeBase;
}
bool GameInstance::gameStateHasChanged() {
	return theEpicFlag.hasChangedPos();
}