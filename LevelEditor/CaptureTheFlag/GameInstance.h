#pragma once

#include "AStarDebugPath.h"
#include "DebugShapeManager.h"
#include "unsigned.h"

//states
#include "RunningToHomeBase.h"
#include "FetchingFlag.h"

//characters
#include "Team.h"
#include "Flag.h"

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


	//STATES ( to give them memory )
	STATES::RunningToHomeBase runningToHomeBaseState;
	STATES::FetchingFlag fetchingFlagState;


	GameInstance() : teamAHomeBaseTransform(nullptr), teamBHomeBaseTransform(nullptr) {}

	void init(AStar::DEBUG::AStarDebugPathGenerator& pather, DebugShapeManager& shaper, uint numOfPlayersPerTeam, glm::mat4 ** teamARenderableTransforms, glm::mat4 ** teamBRenderableTransforms, glm::mat4 * flagRenderableTransform);
	void registerBaseTransforms(glm::mat4 * teamAHomeBaseTransform, glm::mat4 * teamBHomeBaseTransform);
	void randomSetBases(GameNode * nodes, uint numOfNodes);
	void update(float dt);
	glm::vec3 getMyBasePos(Team * myTeam);
	bool gameStateHasChanged();
};