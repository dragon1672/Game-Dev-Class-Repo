#pragma once
#ifndef PARTICAL_EFFECT_H
#define PARTICAL_EFFECT_H

#include "GameGlobal.h"

#include "Vector 2.h"
#include "Core.h"
//#include "Partical.h"
class Partical;

class ParticalEffect {
public:
	static const float defaulMinVel;
	static const float defaulMaxVel;
	virtual void initPartical(Partical *toInit)=0;
	virtual void update(float dt, Partical *toUpdate)=0;
	virtual void draw(MyGraphics& graphics, Partical *toUpdate)=0;
};

#endif