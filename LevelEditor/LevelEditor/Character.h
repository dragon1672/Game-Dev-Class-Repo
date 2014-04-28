#pragma once

#include "AStarPath.h"
#include "Renderer.h"
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Character {
public:
	AStar::Path path;
	glm::mat4 * transformMat;
	glm::vec3 lastPos;
	glm::vec3 direction;

	float currentPercent;
	float progressionPercent;

	void nextNode();
public:
	void init(glm::mat4 * transformMat);

	bool isComplete();

	void setPath(AStar::Path& toSet);

	void update(float dt);
};