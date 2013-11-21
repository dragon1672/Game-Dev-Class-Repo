#pragma once
#ifndef STATIC_POS_H
#define STATIC_POS_H

#include "DynamicPosition.h"

class StaticPos : DynamicPosition {
private:
	Vector2D pos;
public:
	StaticPos() { ; }
	StaticPos(const Vector2D& pos) {
		setPos(pos);
	}
	void setPos(const Vector2D& pos);
	Vector2D getPos();
};

#endif