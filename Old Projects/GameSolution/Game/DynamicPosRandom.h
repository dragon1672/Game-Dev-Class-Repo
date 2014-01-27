#pragma once
#ifndef DYNAMIC_POS_RANDOM_H
#define DYNAMIC_POS_RANDOM_H

#include "DynamicPosition.h"

class DynamicPosRandom : public DynamicPosition {
private:
	float width,height;
public:
	DynamicPosRandom() { ; }
	DynamicPosRandom(float width, float height) {
		init(width,height);
	}
	void init(float width, float height);
	Vector2D getPos();
};

#endif