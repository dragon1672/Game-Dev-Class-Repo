#pragma once
#ifndef PARTICAL_EFFECT_H
#define PARTICAL_EFFECT_H

#include "Vector 2.h"
#include "Core.h"

class Partical;
class MyGraphics;

class ParticalEffect {
public:
	static const float defaulMinVel;
	static const float defaulMaxVel;
	virtual void initPartical(Partical *toInit)=0;
	virtual void update(float dt, Partical *toUpdate)=0;
	virtual void draw(MyGraphics& graphics, Partical *toUpdate)=0;
};

#endif