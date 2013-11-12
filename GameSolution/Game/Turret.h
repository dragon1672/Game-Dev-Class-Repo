#pragma once
#ifndef TURRET_H
#define TURRET_H

#include "Core.h"
#include "Shape.h"
#include "Vector 2.h"

class Turret {
	Shape style;

public:
	void update(float dt) {

	}
	void draw(Core::Graphics graphics) {
		Vector2D mouse = Vector2D(Core::Input::GetMouseX(), Core::Input::GetMouseY());
		Matrix3D();
		style.draw(graphics);
	}
};

#endif