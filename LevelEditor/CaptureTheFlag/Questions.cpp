#include "Questions.h"

#include "Character.h"
#include "Team.h"

bool doIHaveTheFlag(Character * p) {
	return p->hasFlag;
}

bool doesMyTeamHaveTheFlag(Character * p) {
	return p->myTeam->hasFlag();
}