#pragma once
#ifndef PARTICAL_EFFECT_H
#define PARTICAL_EFFECT_H

#include "Vector 2.h"
#include "Partical.h"

const int MAX_PARTICALS = 10000;

class ParticalEffect {
protected:
	Partical particals[MAX_PARTICALS];
	int numParticals;
public:
	virtual void init(int size, const Vector2D& pos, float lifetime);
	virtual void update(float dt);
	virtual void draw(Core::Graphics graphics);
};

#endif