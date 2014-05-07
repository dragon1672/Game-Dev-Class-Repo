#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "MyRandom.h"

class Character;

class Flag {
public:
	float angle;
	float timeSinceLastMove;
	Character * holder;
	glm::vec3 pos;
	Flag() {
		holder = nullptr;
		transformMat = nullptr;
		angle = 0;
		timeSinceLastMove = 0;
	}
	void init(glm::mat4 * transformMat);
	bool hasChangedPos();
	void update(float dt);
	void reset();
	bool grab(Character * guyGrabbing);
private:
	glm::vec3 lastPos;
	glm::mat4 * transformMat;
};