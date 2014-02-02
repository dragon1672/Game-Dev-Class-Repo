#pragma once

#include "DrawnObj.h"
#include <glm/glm.hpp>

class GameObj {
public:
	int accRange;
	int rateToChageAngleACC;
	DrawnObj myShape;
	glm::vec3 translation;
	float scale;
	float xRot;
	float yRot;
	float zRot;
	float xRotAcc;
	float yRotAcc;
	float zRotAcc;

//public:
	GameObj() {
		xRot = 0;
		yRot = 0;
		zRot = 0;

		accRange = 10;
		rateToChageAngleACC = 1000;

		randomizeAngleAcc();
	}

	void randomizeAngleAcc();

	void update(uint frames);

	DrawnObj getShape();

	glm::vec3 getTranslate();
	glm::mat4x4 getTransform();
	glm::mat3x3 getRotationMat();
};