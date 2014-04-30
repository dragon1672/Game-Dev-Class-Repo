#include "CharacterLerp.h"

void CharacterLerp::nextNode() {
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
void CharacterLerp::init(glm::mat4 * transformMat) {
	this->transformMat = transformMat;
	currentPercent = -1;
	speed = 1;
}
bool CharacterLerp::isComplete() {
	return path.isComplete();
}
void CharacterLerp::setPath(AStar::Path& toSet, DebugShapeManager& manager) {
	path.load(toSet);
	path.drawPath(manager);
}
glm::vec3 CharacterLerp::getPos() {
	glm::vec3 pos = glm::vec3((*transformMat) * glm::vec4());
	return pos;
}
void CharacterLerp::update(float dt) {
	currentPercent += speed * (progressionPercent * dt);

	if(0 > currentPercent || currentPercent > 1)
		nextNode();

	glm::vec3 pos = glm::lerp(lastPos,path.currentDestination,currentPercent);
	pos += glm::vec3(0,3,0);
	(*transformMat) = glm::translate(pos) * glm::orientation(direction,glm::vec3(-1,0,0));
}
glm::mat4x4 CharacterLerp::getWorld2View() {
	glm::vec3 pos = glm::lerp(lastPos,path.currentDestination,currentPercent);
	pos+=glm::vec3(0,7,0) + 4.0f * direction;
	return glm::lookAt(pos,pos-direction,glm::vec3(0,1,0));
}