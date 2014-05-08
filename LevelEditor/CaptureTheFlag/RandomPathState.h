#pragma once

#include "State.h"

namespace STATES {

class RandomPathState : public State {
public:
	void init(Character * player, State * lastStates);
	void update(Character * player);
};

}