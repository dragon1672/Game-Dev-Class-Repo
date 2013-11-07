#pragma once

#include "Vector 2.h"
#include "graphics.h"

class Wall {
	Vector2D start;
	Vector2D end;
	Vector2D norm;
public:
	void init(Vector2D start, Vector2D end);
	bool hasCollided(Vector2D pos);
	Vector2D collideVector(Vector2D pos, Vector2D vel);
	void draw(Core::Graphics graphics);
};