#pragma once

#include "AStarPath.h"
#include "AStarDebugPath.h"
#include "Renderer.h"

class CharacterLerp {
public:
	AStar::DEBUG::DebugPath path;
	glm::mat4 * transformMat;
	glm::vec3 lastPos;
	glm::vec3 direction;
	glm::vec3 pos;

	float currentPercent;
	float progressionPercent;
	float speed;

	void nextNode();
public:
	void init(glm::mat4 * transformMat);

	bool isComplete();
	glm::vec3 getPos();
	void changePath(AStar::Path& toSet, DebugShapeManager& manager);
	void setPath(AStar::Path& toSet, DebugShapeManager& manager);

	void update(float dt);
	glm::mat4x4 getWorld2View();
};