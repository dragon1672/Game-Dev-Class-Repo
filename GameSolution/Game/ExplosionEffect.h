/*
#pragma once
#ifndef EXPLOSION_EFFECT_H
#define EXPLOSION_EFFECT_H

#include "ParticalEffect.h"

class ExplosionEffect : ParticalEffect {
private:
	float lifetime;
	float size;
	Vector2D orgin;
public:
	void init(float lifetime, const Vector2D& pos);
	//overloads
	void initPartical(Partical *toInit);
	void update(float dt, Partical *toUpdate);
	void draw(Core::Graphics graphics, Partical *toDraw);
};

#endif
//*/