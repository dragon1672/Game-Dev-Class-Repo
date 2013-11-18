/*
#pragma once
#ifndef PARTICAL_EFFECT_H
#define PARTICAL_EFFECT_H

#include "Vector 2.h"
#include "Partical.h"

class ParticalEffect {
public:
	static const float defaulMinVel;
	static const float defaulMaxVel;
	virtual void initPartical(Partical *toInit);
	virtual void update(float dt, Partical *toUpdate);
	virtual void draw(Core::Graphics graphics, Partical *toUpdate);
};

const float ParticalEffect::defaulMinVel = 5;
const float ParticalEffect::defaulMaxVel = 100;

#endif
//*/