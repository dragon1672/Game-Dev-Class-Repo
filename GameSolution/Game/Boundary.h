#pragma once

#include <varargs.h>
#include "Vector 2.h"
#include "Core.h"
#include "Matrix3D.h"
#include "Wall.h"

class Boundary {
	static Core::RGB defaultColor;
	Wall *walls;
	int numOfWalls;
	bool started;
public:
	Boundary() {
		started = false;
	}
	void init(int count,...);
	void init(int count, Vector2D *points,const Matrix3D& transform=Matrix3D());
	bool hasCollided(Vector2D pos);
	Vector2D collideVector(Vector2D pos, Vector2D vel);
	void draw(Core::Graphics graphics);
};