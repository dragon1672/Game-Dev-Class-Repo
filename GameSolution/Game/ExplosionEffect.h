#pragma once
#ifndef EXPLOSION_EFFECT_H
#define EXPLOSION_EFFECT_H

#include "ParticalEffect.h"

class ExplosionEffect : ParticalEffect {
	Partical particals[MAX_PARTICALS];
	int numParticals;
public:
	void init(int size, const Vector2D& pos, float lifetime);
	void update(float dt);
	void draw(Core::Graphics graphics);
};

#endif