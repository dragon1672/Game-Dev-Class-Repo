#pragma once
#ifndef SOLAR_SYSTEM_MANAGER_H
#define SOLAR_SYSTEM_MANAGER_H

#include "SolarSystem.h"

#define MAX_DEPTH 4
#define MAX_ORBITERS 2
#define LENGTH_POW_DEPTH 16 //2^4
const float ANGLES_IN_CIRCLE = 2*3.14f;

class SolarSystemManager {
	SolarSystem totalSystem[LENGTH_POW_DEPTH];
	SolarSystem firstLayer[MAX_ORBITERS];
	int depth;
	int orbiters;
public:
	void update(float dt) {
		for (unsigned int i=0; i<orbiters; i++)
			firstLayer[i].update(dt);
	}
	void draw(Core::Graphics graphics,const Matrix3D& transform) {
		for (unsigned int i=0; i<orbiters; i++)
			firstLayer[i].draw(graphics,transform);
	}
	void startUp(int depth, int orbiters) {
		this->depth = depth;
		this->orbiters = orbiters;

	}
	void shutdown() {

	}
};

#endif