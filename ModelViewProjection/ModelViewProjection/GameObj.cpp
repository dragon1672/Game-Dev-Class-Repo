#include <GL\glew.h>

#include "GameObj.h"
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtx/transform.hpp"

#include "MyRandom.h"

void GameObj::randomizeAngleAcc() {
	xRotAcc	= RANDOM::randomFloat(-(float)accRange,(float)accRange);
	yRotAcc	= RANDOM::randomFloat(-(float)accRange,(float)accRange);
	zRotAcc	= RANDOM::randomFloat(-(float)accRange,(float)accRange);
}

void GameObj::update(uint frames) {
	xRot += xRotAcc;
	yRot += yRotAcc;
	zRot += zRotAcc;
	if(frames % rateToChageAngleACC == 0) {
		randomizeAngleAcc();
	}
}

DrawnObj GameObj::getShape() {
	return myShape;
}

glm::mat4x4 GameObj::getTransform() {
	return glm::translate(translation)
			* glm::rotate(xRot,glm::vec3(1,0,0))
			* glm::rotate(yRot,glm::vec3(0,1,0))
			* glm::rotate(zRot,glm::vec3(0,0,1))
			* glm::scale(glm::vec3(scale,scale,scale));
}