#pragma once
#ifndef TARGET_MOUSE_H
#define TARGET_MOUSE_H

#include "DynamicPosition.h"

class TargetMouse : public DynamicPosition {
	Vector2D offset;
public:
	TargetMouse() : offset(Vector2D(0,0)) {}
	void init(const Vector2D& offset);
	Vector2D getPos();
};

#endif