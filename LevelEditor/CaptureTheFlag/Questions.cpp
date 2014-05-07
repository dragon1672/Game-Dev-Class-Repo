#include "Questions.h"

#include "Character.h"

bool doIHaveTheFlag(Character * p) {
	return p->hasFlag;
}

bool doesMyTeamHaveTheFlag(Character * p) {
	p->myTeam->hasFlag();
}