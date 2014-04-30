#include "Character.h"

void Character::nextNode() {
	if(!path.isComplete()) {
		currentPercent = 0;
		lastPos = path.currentDestination;
		glm::vec3 newPos = path.popCurrentConnection();

		direction = lastPos - newPos;
		float length = glm::length(direction);
		direction = glm::normalize(direction);

		progressionPercent = 50/length;
	} else {
		currentPercent = 1;
	}
}
void Character::init(glm::mat4 * transformMat) {
	this->transformMat = transformMat;
	currentPercent = -1;
	speed = 1;
	progressionPercent = 1;
	lastPos = glm::vec3(0,0,0);
}
bool Character::isComplete() {
	return path.isComplete();
}
void Character::setPath(AStar::Path& toSet, DebugShapeManager& manager) {
	path.load(toSet);
	path.drawPath(manager);
}
glm::vec3 Character::getPos() {
	return pos;
}
void Character::update(float dt) {
	currentPercent += speed * (progressionPercent * dt);

	if(0 > currentPercent || currentPercent > 1)
		nextNode();

	pos = glm::lerp(lastPos,path.currentDestination,currentPercent);
	(*transformMat) = glm::translate(pos+ glm::vec3(0,3,0)) * glm::orientation(direction,glm::vec3(-1,0,0));
}
glm::mat4x4 Character::getWorld2View() {
	glm::vec3 pos = glm::lerp(lastPos,path.currentDestination,currentPercent);
	pos+=glm::vec3(0,7,0) + 4.0f * direction;
	return glm::lookAt(pos,pos-direction,glm::vec3(0,1,0));
}