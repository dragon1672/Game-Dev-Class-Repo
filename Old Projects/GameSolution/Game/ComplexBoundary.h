#pragma once
#ifndef COMPLEX_BOUNDARY
#define COMPLES_BOUNDARY

#include "HitInfo.h"
#include "Wall.h"
#include "Boundary.h"
#include "Matrix3D.h"

#define MAX_NUMBER_OF_WALLS 100

class ComplexBoundary : public Boundary {
	Wall walls[MAX_NUMBER_OF_WALLS];
	int numOfWalls;
public:
	void     init(int count, Vector2D *points,const Matrix3D& transform=Matrix3D());
	virtual bool     hasCollided  (const Vector2D& pos);
	virtual HitInfo  collideVector(const Vector2D& pos, const Vector2D& vel);
	virtual void     draw(MyGraphics& graphics);
};

#endif