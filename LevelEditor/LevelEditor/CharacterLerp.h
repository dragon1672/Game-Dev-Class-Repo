#pragma once

#include "AStarPath.h"
#include "AStarDebugPath.h"
#include "Renderer.h"
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/rotate_vector.hpp>

class CharacterLerp {
public:
	AStar::DEBUG::DebugPath path;
	glm::mat4 * transformMat;
	glm::vec3 lastPos;
	glm::vec3 direction;

	float currentPercent;
	float progressionPercent;
	float speed;

	void nextNode();
public:
	void init(glm::mat4 * transformMat);

	bool isComplete();
	glm::vec3 getPos();
	void setPath(AStar::Path& toSet, DebugShapeManager& manager);

	void update(float dt);
	glm::mat4x4 getWorld2View();
};