#pragma once
#ifndef TURRET_H
#define TURRET_H

#include "Core.h"
#include "Shape.h"
#include "Vector 2.h"

//make bullet array
//make bullet class
//make bullets draw themselves
//hold's pos, velocity, teamID (to toggle friendly fire)

class Turret {
	Shape *style;
	Vector2D direction;
	Vector2D bullets
public:
	Turret();
	void init();
	void update(float dt, const Vector2D& pos);
	void draw(Core::Graphics& graphics, const Vector2D& pos);
};

#endif