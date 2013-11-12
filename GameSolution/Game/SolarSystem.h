#pragma once
#ifndef SOLAR_SYSTEM_H


#include "Core.h"
#include "Shape.h"
#include <vector>


class SolarSystem {
	static Shape thisStyle;
	
	float orbitAcc;
	float orbitPercent;
	float orbitLength;
	float scale;

	std::vector<SolarSystem> children;
public:
	SolarSystem() {
		orbitAcc     = 5;
		orbitPercent = 25;
		orbitLength  = 40;
		scale        = 100;
	}
	void addChild(const SolarSystem& toAdd);
	void update(float dt);
	void draw(Core::Graphics graphic, const Vector2D& inRefTo);
	void startup(int depth);
};

#endif