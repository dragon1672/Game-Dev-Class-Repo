#pragma once

#include "DrawnObj.h"
#include <glm/glm.hpp>

class GameObj {
public:
	static const int accRange = 10;
	static const int rateToChageAngleACC = 1000;
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
		randomizeAngleAcc();
	}

	void randomizeAngleAcc();

	void update(uint frames);

	DrawnObj getShape();

	glm::mat4x4 getTransform();
};