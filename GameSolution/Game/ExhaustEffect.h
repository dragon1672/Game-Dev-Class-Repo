#pragma once
#ifndef EXHAUST_EFFECT_H
#define EXHAUST_Effect_H

#include "ParticalEffect.h"
#include "GameEntity.h"

class MyGraphics;

class ExhaustEffect : public ParticalEffect {
	GameEntity *parent;
	float lifetime;
	float varianceAngle;
	bool active;
public:
	bool paused;
	void init(GameEntity *parent, float lifetime, float varianceAngle=.5);
	void shutdown();
	//overloads
	void initPartical(Partical *toInit);
	void update(float dt, Partical *toUpdate);
	void draw(MyGraphics& graphics, Partical *toUpdate);
};

#endif