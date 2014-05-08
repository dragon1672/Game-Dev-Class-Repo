#pragma once

#include "AStarDebugPathGenerator.h"
#include "DebugShapeManager.h"
#include "unsigned.h"

//states
#include "RunningToHomeBase.h"
#include "FetchingFlag.h"
#include "RandomPathState.h"

//characters
#include "Team.h"
#include "Flag.h"
#include "CTFBase.h"

class GameInstance {
public:
	Team theATeam;
	Team theBTeam;
	Flag theEpicFlag;

	CTFBase aBase;
	CTFBase bBase;

	AStar::DEBUG::AStarDebugPathGenerator * pather;
	DebugShapeManager* shaper;


	//STATES ( to give them memory )
	STATES::RunningToHomeBase runningToHomeBaseState;
	STATES::FetchingFlag fetchingFlagState;
	STATES::RandomPathState randomPathState;


	void init(AStar::DEBUG::AStarDebugPathGenerator& pather, DebugShapeManager& shaper, uint numOfPlayersPerTeam, glm::mat4 ** teamARenderableTransforms, glm::mat4 ** teamBRenderableTransforms, glm::mat4 * flagRenderableTransform);
	void registerBaseTransforms(glm::mat4 * teamAHomeBaseTransform, glm::mat4 * teamBHomeBaseTransform);
	void randomSetBases(GameNode * nodes, uint numOfNodes);
	void update(float dt);

	CTFBase * getEnemyBase(Character * leDude);
	CTFBase * getMyBase(Character * leDude);
	glm::vec3 getMyBasePos(Team * myTeam);
	bool gameStateHasChanged();
	void scorePoint(Character * leDude);
	void checkPlayerCollisions();
};