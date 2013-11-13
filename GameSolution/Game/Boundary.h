#pragma once
#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "Vector 2.h"
#include "Core.h"
#include "Matrix3D.h"
#include "Wall.h"
#define MAX_NUMBER_OF_WALLS 1000
class Boundary {
protected:
	static Core::RGB defaultColor;
public:
	virtual bool     hasCollided  (const Vector2D& pos)=0;
	virtual Vector2D collideVector(const Vector2D& pos, const Vector2D& vel)=0;
	virtual void     draw(Core::Graphics& graphics)=0;
};

#endif