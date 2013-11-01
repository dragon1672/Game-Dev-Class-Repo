#pragma once

#include "Vector 2.h"
#include "Core.h"
#include "Shape.h"

class GameObject{
protected:
	Vector2D pos;
	Shape thisStyle;
public:
	virtual void update(float dt) = 0;
	virtual void draw(Core::Graphics graphics) = 0;
};