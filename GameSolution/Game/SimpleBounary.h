#pragma once
#ifndef SIMPLE_BOUNDARY
#define SIMPLE_BOUNDARY

#include "Boundary.h"
#include "HitInfo.h"

class SimpleBoundary : public Boundary {
	float x1;
	float y1;
	float x2;
	float y2;
public:
	void init(float x1, float y1, float x2, float y2);
	virtual bool     hasCollided  (const Vector2D& pos);
	virtual HitInfo  collideVector(const Vector2D& pos, const Vector2D& vel);
	virtual void     draw(Core::Graphics& graphics);
};

#endif