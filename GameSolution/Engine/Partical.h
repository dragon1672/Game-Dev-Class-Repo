#pragma once
#ifndef PARTICAL_H
#define PARTICAL_H

#include "Vector 2.h"
#include "Core.h"

class Partical {
public:
	Vector2D pos;
	Vector2D vel;
	Core::RGB color;
	float lifetime;
	inline void update(float dt) {
		pos = pos + vel*dt;
		lifetime -= dt;
	}
};

#endif