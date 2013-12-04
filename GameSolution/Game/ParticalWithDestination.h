#pragma once

#include "Vector 2.h"
#include "Core.h"

class ParticalWithDestination {
private:
	Vector2D vel;
public:
	static float PARTICAL_SPEED;
	Vector2D pos;
	Vector2D target;
	Core::RGB color;
	int size;
	void updateVelToTarget();
	void updateVelToPos(Vector2D& newTarget);
	void update(float dt);
};