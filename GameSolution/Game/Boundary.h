#pragma once
#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "Core.h"
#include "HitInfo.h"

class MyGraphics;

class Boundary {
protected:
	static Core::RGB defaultColor;
public:
	virtual bool     hasCollided  (const Vector2D& pos)=0;
	virtual HitInfo  collideVector(const Vector2D& pos, const Vector2D& vel)=0;
	virtual void     draw(MyGraphics& graphics)=0;
};

#endif