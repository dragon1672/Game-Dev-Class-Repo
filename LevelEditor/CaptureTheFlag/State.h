#pragma once

class Character;

namespace STATES {

class State {
public:
	virtual void init(Character * player) = 0;
	virtual void update(Character * player) = 0;
};

}