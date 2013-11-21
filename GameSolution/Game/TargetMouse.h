#pragma once
#ifndef TARGET_MOUSE_H
#define TARGET_MOUSE_H

#include "DynamicPosition.h"

class TargetMouse : public DynamicPosition {
public:
	Vector2D getPos();
};

#endif