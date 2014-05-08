#include "Character.h"
#include <limits>
#include "GameInstance.h"
#include "Team.h"
#include "Flag.h"

void Character::prepForNextDest() {
	currentDestination = path.popCurrentConnection();
	if(pos != currentDestination) {
		direction = glm::normalize(currentDestination - pos);
	}
}
Flag * Character::getFlag() {
	return myTeam->getFlag();
}
GameInstance * Character::getGame() {
	return myTeam->gameInstance;
}
void Character::init(glm::mat4 * transformMat, Team * myTeam) {
	this->transformMat = transformMat;
	this->myTeam = myTeam;
	speed = 10;
}
AStar::DEBUG::AStarDebugPathGenerator * Character::getPather() {
	return getGame()->pather;
}

void Character::respawn() {
	glm::vec3 offset = Random::glmRand::randomFloatVectorInBoxRanged(10,0,10);
	pos = myTeam->getBase() + offset;
	setNewDestPos(finalDestination);
}

void Character::changePath(AStar::Path& newOne) {
	path.load(newOne);
	//currentDestination = path.popCurrentConnection();
	path.drawPath(*getGame()->shaper);
	path.setVisability(debugPath);
}
void Character::setNewDestPos(glm::vec3& newPos) {
	changePath(getPather()->getPath(currentDestination,newPos));
	//path.currentDestination = currentDestination;
	prepForNextDest();
	finalDestination = newPos;
}

void Character::runDecisionTree() {
	myState = theSmartTree->eval(this);
	myState->init(this,myState_last);
	myState_last = myState;
}

void Character::update(float dt) {
	if(myState!=nullptr) {
		myState->update(this);

		if(getGame()->gameStateHasChanged()) {
			if(theSmartTree!= nullptr) {
				myState = theSmartTree->eval(this);
				myState->init(this,myState_last);
			} else { // if no decision tree is given
				setNewDestPos(getFlag()->pos);
			}
		}

		myState_last = myState;
	} else {
		myState = theSmartTree->eval(this);
		myState->init(this,myState_last);
	}
	glm::vec3 path2Dest = currentDestination - pos;
	glm::vec3 movement = direction * speed * dt * speedMultiplyer;
	if(glm::dot(path2Dest,path2Dest) <= glm::dot(movement,movement)) { // destination will be reached within the tick
		pos = currentDestination;
		prepForNextDest();
	} else {
		pos += movement;
	}
	if(hasFlag) {
		getFlag()->pos = pos + glm::vec3(0,2,0) - 2.0f * direction;
	}

	if(debugPath != lastDebugPath) {
		path.setVisability(debugPath);
		lastDebugPath = debugPath;
	}

	(*transformMat) = glm::translate(pos+ glm::vec3(0,3,0)) * glm::orientation(direction,glm::vec3(1,0,0));
}
glm::mat4x4 Character::getWorld2View() {
	glm::vec3 pos = this->pos;
	pos+=glm::vec3(0,7,0) + 4.0f * direction;
	return glm::lookAt(pos,pos-direction,glm::vec3(0,1,0));
}