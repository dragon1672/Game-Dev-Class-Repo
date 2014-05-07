#include "Questions.h"

#include "Character.h"
#include "Team.h"
#include "DecisionTreeNode.h"
#include "GameInstance.h"

bool doIHaveTheFlag(Character * p) {
	return p->hasFlag;
}

bool doesMyTeamHaveTheFlag(Character * p) {
	return p->myTeam->hasFlag();
}

DecisionTreeNode basicTree[5];

DecisionTreeNode * getBasicTree(GameInstance * ctxt) {
	basicTree[0].question = doIHaveTheFlag;
	basicTree[0].left  = &basicTree[1];
	basicTree[0].right = &basicTree[2]; // 0 complete
	basicTree[1].question = doesMyTeamHaveTheFlag;
	basicTree[1].left  = &basicTree[3];
	basicTree[1].right = &basicTree[4]; // 1 complete
	basicTree[2].state = &ctxt->runningToHomeBaseState;
	basicTree[3].state = &ctxt->fetchingFlagState;
	basicTree[4].state = &ctxt->randomPathState;
	return basicTree;
}