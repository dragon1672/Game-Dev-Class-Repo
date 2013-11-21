#pragma once
#ifndef DYNAMIC_POSITION_H
#define DYNAMIC_POSITION_H

#include "Vector 2.h"

class DynamicPosition {
public:
	virtual Vector2D getPos()=0;
};

#endif