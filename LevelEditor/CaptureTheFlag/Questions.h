#pragma once

#include "DecisionTreeNode.h"s

class Character;
class GameInstance;

bool doIHaveTheFlag(Character * p);

bool doesMyTeamHaveTheFlag(Character * p);

DecisionTreeNode * getBasicTree(GameInstance * ctxt);