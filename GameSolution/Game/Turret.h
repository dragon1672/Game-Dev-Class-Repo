#pragma once
#ifndef TURRET_H
#define TURRET_H

#include "Core.h"
#include "Shape.h"
#include "Vector 2.h"

class Turret {
	Shape *style;
	Vector2D direction;
public:
	Turret();
	void init();
	void update(float dt, const Vector2D& pos);
	void draw(Core::Graphics& graphics, const Vector2D& pos);
};

#endif