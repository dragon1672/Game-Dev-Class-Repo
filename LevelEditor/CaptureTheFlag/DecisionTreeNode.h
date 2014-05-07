#pragma once

#include "State.h"

class Character;


typedef bool (*QUESTION)(Character * player);

struct DecisionTreeNode {
	DecisionTreeNode * left;
	DecisionTreeNode * right;

	QUESTION question;

	STATES::State * state;

	DecisionTreeNode() : left(nullptr), right(nullptr), state(nullptr) {}

	inline STATES::State * eval(Character * player) {
		if(left == nullptr || right == nullptr)
			return state;
		return (question(player))? right->eval(player) : left->eval(player);
	}
};