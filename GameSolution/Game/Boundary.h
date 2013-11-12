#pragma once

#include <varargs.h>
#include "Vector 2.h"
#include "Core.h"
#include "Matrix3D.h"
#include "Wall.h"
#define MAX_NUMBER_OF_WALLS 1000
class Boundary {
	static Core::RGB defaultColor;
	Wall walls[MAX_NUMBER_OF_WALLS];
	int numOfWalls;
public:
	void     init(int count, Vector2D *points,const Matrix3D& transform=Matrix3D());
	bool     hasCollided  (const Vector2D& pos);
	Vector2D collideVector(const Vector2D& pos, const Vector2D& vel);
	void     draw(Core::Graphics& graphics);
};