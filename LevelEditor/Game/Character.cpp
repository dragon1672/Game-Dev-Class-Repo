#include "Character.h"

void Character::nextNode() {
	if(!path.isComplete()) {
		currentPercent = 0;
		lastPos = path.currentDestination;
		glm::vec3 newPos = path.popCurrentConnection();

		direction = lastPos - newPos;
		float length = glm::length(direction);
		direction = glm::normalize(direction);

		progressionPercent = .25/length;
	} else {
		currentPercent = 1;
	}
}
void Character::init(glm::mat4 * transformMat) {
	this->transformMat = transformMat;
	currentPercent = -1;
	path.positions.push_back(glm::vec3(10, 0,20));
	path.positions.push_back(glm::vec3(15, 0,30));
	path.positions.push_back(glm::vec3(20,10,10));
	path.positions.push_back(glm::vec3(25, 0,15));
	path.positions.push_back(glm::vec3(30, 0,20));
	path.positions.push_back(glm::vec3(35, 0,10));
}
bool Character::isComplete() {
	return path.isComplete();
}
void Character::setPath(AStar::Path& toSet) {
	path = toSet;
}
void Character::update(float dt) {
	currentPercent += progressionPercent * dt;

	if(0 > currentPercent || currentPercent > 1)
		nextNode();

	glm::vec3 pos = glm::lerp(lastPos,path.currentDestination,currentPercent);
	pos += glm::vec3(0,3,0);
	//direction = glm::vec3(1,0,0);
	(*transformMat) = glm::translate(pos) * glm::orientation(direction,glm::vec3(-1,0,0));
}