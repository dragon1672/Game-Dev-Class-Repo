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
void Character::init(glm::mat4 * transformMat, Team * myTeam) {
	this->transformMat = transformMat;
	this->myTeam = myTeam;
	speed = 10;
}
void Character::reset() {
	/*
	if(myState == State::RunningToHomeBaseState) {
		setNewDestPos(homeBasePos);
		hasFlag = true;
		meFlag->holder = this;
		meFlag->timeSinceLastMove = std::numeric_limits<float>::infinity();
	} else if(myState==State::FetchingFlagState) {
		meFlag->reset();
		changePath(pather->getPath(pos,meFlag->pos));
		finalDestination = meFlag->pos;
		hasFlag = false;
	}
	//*/
}
void Character::changePath(AStar::Path& newOne) {
	path.load(newOne);
	currentDestination = path.popCurrentConnection();
	path.drawPath(*this->myTeam->gameInstance->shaper);
	path.setVisability(debugPath);
}
void Character::setNewDestPos(glm::vec3& newPos) {
	changePath(this->myTeam->gameInstance->pather->getPath(pos,newPos));
	prepForNextDest();
	finalDestination = newPos;
}
void Character::newFlagPos(glm::vec3 newPos) {
	//if(myState == State::FetchingFlagState) {
	//	setNewDestPos(newPos);
	//}
}
void Character::update(float dt) {
	if(myTeam->getFlag()->hasChangedPos()) {
		setNewDestPos(myTeam->getFlag()->pos);
	} else {
		glm::vec3 path2Dest = currentDestination - pos;
		glm::vec3 movement = direction * speed * dt * speedMultiplyer;
		if(glm::dot(path2Dest,path2Dest) <= glm::dot(movement,movement)) { // destination will be reached within the tick
			pos = currentDestination;
			prepForNextDest();
		} else {
			pos += movement;
		}

		if(debugPath != lastDebugPath) {
			path.setVisability(debugPath);
			lastDebugPath = debugPath;
		}

		(*transformMat) = glm::translate(pos+ glm::vec3(0,3,0)) * glm::orientation(direction,glm::vec3(1,0,0));
	}
}
glm::mat4x4 Character::getWorld2View() {
	glm::vec3 pos = this->pos;
	pos+=glm::vec3(0,7,0) + 4.0f * direction;
	return glm::lookAt(pos,pos-direction,glm::vec3(0,1,0));
}