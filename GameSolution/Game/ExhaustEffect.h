//*
#pragma once
#ifndef EXHAUST_EFFECT_H
#define EXHAUST_Effect_H

#include "ParticalEffect.h"
#include "GameEntity.h"

class ExhaustEffect : public ParticalEffect {
	GameEntity *parent;
	float lifetime;
	float varianceAngle;
public:
	void init(GameEntity *parent, float lifetime, float varianceAngle=.5);
	//overloads
	void initPartical(Partical *toInit);
	void update(float dt, Partical *toUpdate);
	void draw(Core::Graphics graphics, Partical *toUpdate);
};

#endif
//*/