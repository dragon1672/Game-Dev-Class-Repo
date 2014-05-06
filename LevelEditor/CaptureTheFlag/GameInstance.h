#pragma once

#include "Character.h"
#include "Flag.h"
#include "RunningToHomeBase.h"
#include "FetchingFlag.h"
#include "AStarDebugPath.h"
#include "DebugShapeManager.h"
#include "unsigned.h"

#include "Team.h"

//to place in CPP
#include "MyRandom.h"
#include "glm/gtx/transform.hpp"

class GameInstance {
public:
	Team theATeam;
	Team theBTeam;
	Flag theEpicFlag;

	glm::vec3 teamAHomeBase;
	glm::mat4 * teamAHomeBaseTransform;
	glm::vec3 teamBHomeBase;
	glm::mat4 * teamBHomeBaseTransform;

	AStar::DEBUG::AStarDebugPathGenerator * pather;
	DebugShapeManager* shaper;

	GameInstance() : teamAHomeBaseTransform(nullptr), teamBHomeBaseTransform(nullptr) {}

	void init(AStar::DEBUG::AStarDebugPathGenerator& pather, DebugShapeManager& shaper, uint numOfPlayersPerTeam, glm::mat4 ** teamARenderableTransforms, glm::mat4 ** teamBRenderableTransforms, glm::mat4 * flagRenderableTransform) {
		this->shaper = &shaper;
		this->pather = &pather;
		theEpicFlag.init(flagRenderableTransform); 
		theATeam.init(this,numOfPlayersPerTeam,teamARenderableTransforms);
		theBTeam.init(this,numOfPlayersPerTeam,teamBRenderableTransforms);
	}
	void registerBaseTransforms(glm::mat4 * teamAHomeBaseTransform, glm::mat4 * teamBHomeBaseTransform) {
		this->teamAHomeBaseTransform = teamAHomeBaseTransform;
		this->teamBHomeBaseTransform = teamBHomeBaseTransform;
		*(teamAHomeBaseTransform) = glm::translate(teamAHomeBase);
		*(teamBHomeBaseTransform) = glm::translate(teamBHomeBase);
	}
	void randomSetBases(GameNode * nodes, uint numOfNodes) {
		int randomIndexForA = Random::randomInt(0,numOfNodes);
		int randomIndexForB = Random::randomInt(0,numOfNodes);
		teamAHomeBase = nodes[randomIndexForA].pos;
		teamBHomeBase = nodes[randomIndexForB].pos;
		if(teamAHomeBaseTransform!= nullptr) *(teamAHomeBaseTransform) = glm::translate(teamAHomeBase);
		if(teamBHomeBaseTransform!= nullptr) *(teamBHomeBaseTransform) = glm::translate(teamBHomeBase);
	}
	void update(float dt) {
		theEpicFlag.update(dt);
		theATeam.update(dt);
		theBTeam.update(dt);
	}
	glm::vec3 getMyBasePos(Team * myTeam) {
		return (myTeam == &theATeam)? teamAHomeBase : teamBHomeBase;
	}
	bool gameStateHasChanged() {

	}
};