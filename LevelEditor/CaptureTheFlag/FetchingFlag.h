#pragma once

#include "State.h"

namespace STATES {

class FetchingFlag : public STATES::State {
public:
	void init(Character * player);
	void update(Character * player);
};

}