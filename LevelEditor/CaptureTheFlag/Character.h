#pragma once

#include "Renderer.h"
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "State.h"
#include "AStarDebugPath.h"
#include "DecisionTreeNode.h"
#include "AStarDebugPathGenerator.h"

class Team;
class Flag;
class GameInstance;
#include "MyRandom.h"

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
	STATES::State * myState_last;
	DecisionTreeNode * theSmartTree;

	Flag * getFlag();
	GameInstance * getGame();
	AStar::DEBUG::AStarDebugPathGenerator * getPather();
private:
	void prepForNextDest();
public:
	Character() {
		hasFlag = false;
		transformMat = nullptr;
		theSmartTree = nullptr;
		myState = nullptr;
		speedMultiplyer = Random::randomFloat(1,2);
		debugPath = true;
		lastDebugPath = true;
	}
	void init(glm::mat4 * transformMat, Team * myTeam);

	void respawn();
	void runDecisionTree();

	void changePath(AStar::Path& newOne);
	//void addPath(AStar::Path& newOne);

	void setNewDestPos(glm::vec3& newPos);

	void update(float dt);
	glm::mat4x4 getWorld2View();
};