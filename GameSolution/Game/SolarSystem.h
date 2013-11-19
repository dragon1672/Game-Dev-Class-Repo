#pragma once
#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include "GameGlobal.h"

#include "Core.h"
#include "Shape.h"
#include <vector>


class SolarSystem {
	static Shape thisStyle;
	std::vector<SolarSystem *> children;
public:
	float orbitAcc;
	float orbitAngle;
	float orbitLength;
	float size;

	SolarSystem() {
		orbitAcc    = 5;
		orbitAngle  = 25;
		orbitLength = 40;
		size        = 1;
	}
	void addChild(SolarSystem *toAdd);
	void update(float dt);
	void draw(Core::Graphics graphic, const Matrix3D& transform);
	void startup(int depth);
};

#endif