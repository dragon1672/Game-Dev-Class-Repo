#pragma once
#ifndef SOLAR_SYSTEM_H


#include "Core.h"
#include "Shape.h"
#include <vector>


class SolarSystem {
	static Shape thisStyle;
	
	float orbitAcc;
	float orbitAngle;
	float orbitLength;
	float size;

	std::vector<SolarSystem *> children;
public:
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