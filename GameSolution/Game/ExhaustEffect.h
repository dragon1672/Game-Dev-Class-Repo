/*
#pragma once
#ifndef EXHAUST_EFFECT_H
#define EXHAUST_Effect_H

#include "ParticalEffect.h"
#include "GameEntity.h"

class ExhaustEffect : public ParticalEffect {
	GameEntity *parent;
	int lifetime;
	float varianceAngle;
public:
	void init(GameEntity *parent, int lifetime=2, float varianceAngle=30);
	//overloads
	void initPartical(Partical *toInit);
	void update(float dt, Partical *toUpdate);
	void draw(Core::Graphics graphics, Partical *toUpdate);
};

#endif
//*/