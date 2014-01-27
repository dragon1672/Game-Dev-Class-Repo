#pragma once
#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include "Core.h"
#include "Shape.h"
#include <vector>


class SolarSystem {
	static Shape thisStyle;
	float orbitAcc;
	float orbitAngle;
	float orbitLength;
	float size;
	int maxDepth;
	int children;

	void draw(MyGraphics& graphics, const Matrix3D& transform, int depth, float scale, int children);
public:
	SolarSystem() {
		orbitAcc    = .5;
		orbitAngle  = 25;
		orbitLength = 50;
		size        = 2.5;
	}
	void update(float dt);
	void draw(MyGraphics& graphics, const Matrix3D& transform);
	void startup(int depth, int children=2);
};

#endif