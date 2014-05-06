#include "Flag.h"

void Flag::init(glm::mat4 * transformMat) {
	this->transformMat = transformMat;
}
bool Flag::hasChangedPos() { return pos != lastPos; }
void Flag::update(float dt) {
	lastPos = pos;
	if(transformMat != nullptr) {
		if((0 >= timeSinceLastMove || timeSinceLastMove > 5) && holder == nullptr) {
			reset();
		}
		timeSinceLastMove += dt;
		if(holder != nullptr) {
			angle += 10;
		}
		*transformMat = glm::translate(pos) * glm::rotate(angle,glm::vec3(0,1,0));
	}

}
void Flag::reset() {
	holder = nullptr;
	pos = Random::glmRand::randomFloatVectorInBoxRanged(30,0,100);
	timeSinceLastMove = 0;
}