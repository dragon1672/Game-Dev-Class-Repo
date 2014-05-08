#include "GameInstance.h"

#include "MyRandom.h"
#include "glm/gtx/transform.hpp"
#include "Questions.h"
#include "DecisionTreeNode.h"
#include "Character.h"

void GameInstance::init(AStar::DEBUG::AStarDebugPathGenerator& pather, DebugShapeManager& shaper, uint numOfPlayersPerTeam, glm::mat4 ** teamARenderableTransforms, glm::mat4 ** teamBRenderableTransforms, glm::mat4 * flagRenderableTransform) {
	this->shaper = &shaper;
	this->pather = &pather;
	theEpicFlag.init(flagRenderableTransform); 
	theATeam.init(this,numOfPlayersPerTeam,teamARenderableTransforms);
	theBTeam.init(this,numOfPlayersPerTeam,teamBRenderableTransforms);
	DecisionTreeNode * parentDecidingNode = getBasicTree(this);
	theATeam.registerWithDecisions(parentDecidingNode);
	theBTeam.registerWithDecisions(parentDecidingNode);
}
void GameInstance::registerBaseTransforms(glm::mat4 * teamAHomeBaseTransform, glm::mat4 * teamBHomeBaseTransform) {
	aBase.setTransform(teamAHomeBaseTransform);
	bBase.setTransform(teamBHomeBaseTransform);
}
void GameInstance::randomSetBases(GameNode * nodes, uint numOfNodes) {
	aBase.setPos(nodes[Random::randomInt(0,numOfNodes)].pos);
	bBase.setPos(nodes[Random::randomInt(0,numOfNodes)].pos);
	theATeam.respawnAll();
	theBTeam.respawnAll();
}
CTFBase * GameInstance::getEnemyBase(Character * leDude) {
	return (leDude->myTeam == &theATeam)? &bBase : &aBase;
}
CTFBase * GameInstance::getMyBase(Character * leDude) {
	return (leDude->myTeam == &theATeam)? &aBase : &bBase;
}
void GameInstance::update(float dt) {
	if(shaper!=nullptr) {
		theATeam.update(dt);
		theBTeam.update(dt);
		checkPlayerCollisions();
		theEpicFlag.update(dt);
	}
}
glm::vec3 GameInstance::getMyBasePos(Team * myTeam) {
	return (myTeam == &theATeam)? aBase.getPos() : bBase.getPos();
}
bool GameInstance::gameStateHasChanged() {
	return theEpicFlag.hasChangedPos();
}

bool gvecInCircleRange(glm::vec3& pos1, glm::vec3& pos2, float errorRadius=.5f) {
	glm::vec3 diff = pos1 - pos2;
	float length = glm::dot(diff,diff);
	return (errorRadius * errorRadius > length);
}

void GameInstance::scorePoint(Character * leDude) {
	CTFBase * playersBase = getMyBase(leDude);
	if(theEpicFlag.holder == leDude && gvecInCircleRange(leDude->pos, playersBase->getPos())) {
		leDude->hasFlag = false;
		theEpicFlag.reset();
		playersBase->scorePoints();
	}
}
void GameInstance::checkPlayerCollisions() {
	if(theEpicFlag.holder!=nullptr) {
		Team * enemyTeam = theEpicFlag.holder->myTeam == &theATeam ? &theBTeam : &theATeam;
		if(enemyTeam->collision(theEpicFlag.holder->pos,.5,.5)) {
			theEpicFlag.holder->hasFlag = false;
			theEpicFlag.holder->respawn();
			theEpicFlag.reset();
		}
	}
}