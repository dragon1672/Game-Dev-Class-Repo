#pragma once
#ifndef COMPLEX_BOUNDARY
#define COMPLES_BOUNDARY

#include "Boundary.h"

class ComplexBoundary : public Boundary {
	Wall walls[MAX_NUMBER_OF_WALLS];
	int numOfWalls;
public:
	void     init(int count, Vector2D *points,const Matrix3D& transform=Matrix3D());
	virtual bool     hasCollided  (const Vector2D& pos);
	virtual Vector2D collideVector(const Vector2D& pos, const Vector2D& vel);
	virtual void     draw(Core::Graphics& graphics);
};

#endif