#pragma once

#include "Vector 2.h"
#include "myGraphics.h"
#include "HitInfo.h"

class Wall {
	Vector2D start;
	Vector2D end;
	Vector2D norm;
public:
	void     init(const Vector2D& start, const Vector2D& end);
	bool     hasCollided(const Vector2D& pos);
	HitInfo  collideVector(const Vector2D& pos, const Vector2D& vel);
	void     draw(MyGraphics& graphics);
};