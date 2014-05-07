#pragma once

#include "AStarPath.h"
#include "AStarDebugPath.h"
#include "Renderer.h"
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "State.h"
#include "AStarDebugPathGenerator.h"
#include "Flag.h"

class Team;

class Character {
public:
	Team * myTeam;

	AStar::DEBUG::DebugPath path;
	glm::mat4 * transformMat;
	float speed;
	glm::vec3 pos;
	glm::vec3 direction;
	glm::vec3 finalDestination;
	glm::vec3 currentDestination;
	
	float speedMultiplyer;
	bool debugPath;
	bool lastDebugPath;

	bool hasFlag;
	STATES::State * myState;
private:
	void prepForNextDest();
	void reset();
public:
	Character() {
		hasFlag = false;
		transformMat = nullptr;
		speedMultiplyer = 1;
		debugPath = true;
		lastDebugPath = true;
	}
	void init(glm::mat4 * transformMat, Team * myTeam);

	void changePath(AStar::Path& newOne);

	void setNewDestPos(glm::vec3& newPos);
	void newFlagPos(glm::vec3 newPos);

	void update(float dt);
	glm::mat4x4 getWorld2View();
};